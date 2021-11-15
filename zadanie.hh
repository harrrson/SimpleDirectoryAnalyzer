#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem;


int iterate_through_directory(fs::path const p, uint& nof, ulong& nol);
void count_lines_in_file(std::string const p, ulong& lc);

