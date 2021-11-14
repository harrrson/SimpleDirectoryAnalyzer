#include "main.hh"

//Iterate through directories, return number of files found and total number of lines
int iterate_through_directory(fs::path const p, uint& nof, ulong& nol)
{
    std::cout<<p<<std::endl;
    if(!fs::exists(p))
    {
        std::cout<<"Path does not exist: "<<p<<'\n';
        return 1;
    }
    for(auto const de : fs::recursive_directory_iterator(p))
    {
        std::cout<<de.is_regular_file()<<' '
        <<de.path()<<'\n';
        if(de.is_regular_file())
        {
            //TODO: Add line counting
        }
    }
    return 0;
}

long count_lines_in_file(fs::directory_entry const de)
{
    
    return 0;
}

int main(int argc, char *argv[])
{
    uint number_of_files = 0;
    ulong number_of_lines = 0;
    fs::path path;
    std::cout<<argc<<'\n';
    //Check, if path was given. If not, take current path
    if(argc > 1)
    {
        //TODO: change to argv
        path = argv[1];//"/mnt/d/VS projekty/BCF_zadanie/test_path";//
    }
    else
    {
        path = fs::current_path();
    }
    std::cout << fs::exists(path) << '\n';
    iterate_through_directory(path, number_of_files, number_of_lines);
    return 0;
}