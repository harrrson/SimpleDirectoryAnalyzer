#include "zadanie.hh"

//Iterate through directories, return number of files found and total number of lines
int iterate_through_directory(fs::path const p, uint& nof, ulong& nol)
{
    std::cout<<p<<std::endl;
    if(!fs::exists(p))
    {
        std::cout<<"Path does not exist: "<<p<<'\n';
        return 1;
    }
    ulong temp_line_count;
    nof=0;
    nol=0;
    for(auto const de : fs::recursive_directory_iterator(p))
    {
        if(de.is_regular_file())
        {
            count_lines_in_file(de.path(),temp_line_count);
            nof+=1;
            nol+=temp_line_count;
        }
    }
    return 0;
}

void count_lines_in_file(std::string const p, ulong& lc)
{
    std::ifstream ifile (p);
    if(!ifile)
    {
        lc=0;
        return;
    }
    lc=0;
    std::string dump;
    while(getline(ifile,dump))
    {
        lc+=1;
    }
}

