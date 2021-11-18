#pragma once
#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>
#include <algorithm>
#include "lineCountData.hh"

//https://stackoverflow.com/a/32593825
/*
Custom thread pool. Constructor defaults to number of threads available in the system (default CPU thread count).

*/
class ThreadPool
{
    public:
    ThreadPool(uint numOfThr = 0);
    ~ThreadPool();
    void queueFile(std::string p);
    lineCountData returnResult();
    int threadCount();

    private:
    void shutdown();
    void threadJob(uint threadIndex);

    private:
    std::vector<std::thread> threadPool;
    std::mutex workMutex;
    //Controls, if threads are doing any work atm. Prevents reading of results when they are working.
    std::vector<bool> workFlag; 
    std::mutex queueMutex;
    std::condition_variable cv;
    std::queue<std::string> fileQueue;
    bool terminatePool = false;
    std::mutex resultMutex;
    lineCountData result;
    bool stopped=false;;
};

#include "zadanie.hh"