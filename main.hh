#pragma once
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


void iterate_through_directory(fs::path const p, int& nof, long& nol);
long count_lines_in_file(fs::directory_entry const de);

