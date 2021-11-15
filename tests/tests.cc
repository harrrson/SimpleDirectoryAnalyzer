#include "gtest/gtest.h"

#include "../zadanie.hh"

class FileParserTest :public ::testing::Test
{
protected:
  void SetUp() override
  {
    fs::create_directories("tests/empty_dir");
    std::ofstream("tests/empty_file.txt");
    std::ofstream("tests/not_empty_file.txt")<<"Some test lines\neven two";
  }

  void TearDown() override
  {
    fs::remove_all("tests");
  }
};

TEST_F(FileParserTest, EmptyLineCount)
{
  ulong line_count=0;
  count_lines_in_file("tests/empty_file.txt",line_count);

  EXPECT_EQ(line_count,0);
}

TEST_F(FileParserTest, NonEmptyLineCount)
{
  ulong line_count=0;
  count_lines_in_file("tests/not_empty_file.txt",line_count);

  EXPECT_EQ(line_count,2);
}

TEST_F(FileParserTest, TestEmptyDir)
{
    fs::path path("tests/empty_dir");
    ulong line_count = -1;
    uint file_count = -1;
    iterate_through_directory(path,file_count,line_count);
    EXPECT_EQ(file_count,0);
    EXPECT_EQ(line_count,0);
}

TEST_F(FileParserTest, NonEmptyEmptyDir)
{
    fs::path path("tests");
    ulong line_count = -1;
    uint file_count = -1;
    int result=iterate_through_directory(path,file_count,line_count);
    EXPECT_EQ(file_count,2);
    EXPECT_EQ(line_count,2);
}