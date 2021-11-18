#include "zadanie.hh"

//Iterate through directories, return number of files found and total number of lines
int iterate_through_directory(fs::path const p, uint& nof, lineCountData& nol, ThreadPool& tp)
{
    if(!fs::exists(p))
    {
        std::cout<<"Path does not exist: "<<p<<'\n';
        return 1;
    }
    lineCountData tempLineCount;
    nof=0;
    nol.lines=0;
    //Iterator handles an recursion for me, i don't need to check for directories anymore
    for(auto const de : fs::recursive_directory_iterator(p))
    {
        //We wnat to check only regular files. Pipes etc are out of our interest.
        if(de.is_regular_file())
        {
            tp.queueFile(de.path());
            nof+=1;
        }
    }
    nol=tp.returnResult();
    return 0;
}

//
void count_lines_in_file(std::string const p, lineCountData& lc)
{
    std::ifstream ifile (p);
    lc.lines=0;
    if(!ifile)
    {
        return;
    }
    std::string line;
    while(getline(ifile,line))
    {
        if(line.empty()) lc.emptyLines+=1;
        else lc.nonEmptyLines+=1; 
        lc.lines+=1;
        if(!line.empty())
        {
            bool nonspaceFound=false;
            for(const char c : line)
            {
                bool charIsSpace = isspace(c)!=0;
                //If there are some consecutive white spaces, we can ignore them
                if(charIsSpace and nonspaceFound)
                {
                    nonspaceFound=false;
                    lc.wordCount+=1;
                }
                else if(!charIsSpace)
                {
                    nonspaceFound=true;
                    lc.letterCount+=1;
                }
            }
        }
    }
}

