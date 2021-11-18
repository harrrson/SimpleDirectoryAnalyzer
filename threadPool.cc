#include "threadPool.hh"

ThreadPool::ThreadPool(uint numOfThr)
{   
    if(numOfThr>2000) std::cout<<"You want "<<numOfThr<<" threads, i see you're brave.\n"
                               <<"Beware, app may halt when too much threads are created!";
    if(numOfThr<1 && std::thread::hardware_concurrency()>0)
    {
        numOfThr=std::thread::hardware_concurrency();
    } 
    else if(numOfThr<1 && std::thread::hardware_concurrency()==0)
    {
        std::cout<<"Cannot get number of system's threads, created 4 threads (Got pretty good times in tests)";
        numOfThr=4;
    }
    for(int i=0; i<numOfThr; i++)
    {
        this->threadPool.push_back(std::thread(&ThreadPool::threadJob, this, i));
        this->workFlag.push_back(false);
    }
}

ThreadPool::~ThreadPool()
{
    if(!this->stopped) this->shutdown();
}

//Push found file paths into queue and wakes any free thread.
void ThreadPool::queueFile(std::string p)
{
    std::unique_lock<std::mutex> lock(this->queueMutex);
    this->fileQueue.push(p);
    this->cv.notify_one();
}

void ThreadPool::shutdown()
{
    this->terminatePool=true;
    this->cv.notify_all();
    for(std::thread &th : this->threadPool)
    {
        th.join();
    }
    this->threadPool.clear();
    this->stopped=true;
    
}

//Default thread job. Waits for any available 
void ThreadPool::threadJob(uint threadIndex)
{
    while(true)
    {
        std::string path;
        {
            std::unique_lock<std::mutex> queueLock(this->queueMutex);
            this->cv.wait(queueLock, [this](){
                return !this->fileQueue.empty() || this->terminatePool;
            });

            
            if(this->terminatePool) break;

            std::unique_lock<std::mutex> workLock(this->workMutex);
            this->workFlag[threadIndex]=true;
            //Let another task begin or end it's work a few nanoseconds earlier, don't wait for end of scope.
            workLock.unlock();
            path = this->fileQueue.front();
            this->fileQueue.pop();
            queueLock.unlock();
        }
        
        
        lineCountData tempLineCount;
        count_lines_in_file(path,tempLineCount);
        {
            std::unique_lock<std::mutex> resultLock(this->resultMutex);
            this->result = this->result + tempLineCount;
            std::unique_lock<std::mutex> workLock(this->workMutex);
            this->workFlag[threadIndex]=false;
            workLock.unlock();
            resultLock.unlock();
        }
    }
}

//Method allows to get result of counting lines, after all threads end their work
lineCountData ThreadPool::returnResult()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(this->queueMutex);
        std::unique_lock<std::mutex> workLock(this->workMutex);
        if(std::none_of(this->workFlag.begin(),this->workFlag.end(),[this](bool v){return v;}) && this->fileQueue.empty())
        {
            break;
        }
        workLock.unlock();
        lock.unlock();
    }
    std::unique_lock<std::mutex> lock(this->resultMutex);
    return result;
}

//Simply returns, how much threads are created at the moment (not necessary available, some can do work now)
int ThreadPool::threadCount()
{
    return this->threadPool.size();
}