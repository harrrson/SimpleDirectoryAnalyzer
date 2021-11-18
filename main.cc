
#include "threadPool.hh"
#include "zadanie.hh"
#include <chrono>

int main(int argc, char *argv[])
{
    fs::path path;
    //Check, if path was given. If not, take current path
    if(argc > 1)
    {
        path = argv[1];
    }
    else
    {
        path = fs::current_path();
    }
    uint numberOfFiles = 0;
    lineCountData inFileCountResult;
    ThreadPool pool;
    auto t1=std::chrono::high_resolution_clock::now();
    int result=iterate_through_directory(path, numberOfFiles, inFileCountResult, pool);
    auto t2=std::chrono::high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout<<"Number of threads: "<<pool.threadCount()<<'\n';
    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n\n";
    std::cout   << "Number of files in directory:       " << numberOfFiles << '\n'
                << "Number of lines in files:           " <<inFileCountResult.lines << '\n'
                << "Number of empty lines in files:     " <<inFileCountResult.emptyLines << '\n'
                << "Number of non empty lines in files: " <<inFileCountResult.nonEmptyLines << '\n'
                << "Number of words in files:           " <<inFileCountResult.wordCount << '\n'
                << "Number of letters in files:         " <<inFileCountResult.letterCount << '\n'
                
                <<std::endl;
    return 0;
}