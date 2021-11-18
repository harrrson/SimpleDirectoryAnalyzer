# Simple Directory Analyzer

## What this program does

Simple program, which analyzes:
- total number of files (only regular files, pipes etc. does not count) (also checks subdirectories)
- total number of lines in files
- total number of words and non-whitespace characters

## Gtest

This program uses [GTest](https://github.com/google/googletest) for unit tests. To test it, add `-Dtest_mode` when configuring Cmake