#include "zadanie.hh"

int main(int argc, char *argv[])
{
    uint number_of_files = 0;
    ulong number_of_lines = 0;
    fs::path path;
    std::cout<<argc<<'\n';
    //Check, if path was given. If not, take current path
    if(argc > 1)
    {
        path = argv[1];
    }
    else
    {
        path = fs::current_path();
    }
    iterate_through_directory(path, number_of_files, number_of_lines);
    return 0;
}