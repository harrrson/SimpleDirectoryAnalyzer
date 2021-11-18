#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include "threadPool.hh"
#include "lineCountData.hh"

namespace fs = std::filesystem;

int iterate_through_directory(fs::path const p, uint& nof, lineCountData& nol, ThreadPool& tp);
void count_lines_in_file(std::string const p, lineCountData& lc);