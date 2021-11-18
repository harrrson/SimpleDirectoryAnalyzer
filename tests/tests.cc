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
    std::ofstream("tests/file_with_empty_lines.txt")
        <<"Some test lines\n"
        <<"\n"
        <<"even two\n"
        <<"\n"
        <<"even have some empty lines";
  }

  void TearDown() override
  {
    fs::remove_all("tests");
  }
};

TEST_F(FileParserTest, EmptyLineCount)
{
  lineCountData lineCount;
  count_lines_in_file("tests/empty_file.txt",lineCount);

  EXPECT_EQ(lineCount.lines,0);
}

TEST_F(FileParserTest, NonEmptyFileLineCount)
{
  lineCountData lineCount;
  count_lines_in_file("tests/not_empty_file.txt",lineCount);

  EXPECT_EQ(lineCount.lines,2);
}

TEST_F(FileParserTest, FileWithEmptyLineCount)
{
  lineCountData lineCount;
  count_lines_in_file("tests/file_with_empty_lines.txt",lineCount);

  EXPECT_EQ(lineCount.lines,5);
  EXPECT_EQ(lineCount.nonEmptyLines,3);
  EXPECT_EQ(lineCount.emptyLines,2);
}

TEST_F(FileParserTest, EmptyDir)
{
    fs::path path("tests/empty_dir");
    lineCountData lineCount;
    uint file_count = -1;
    ThreadPool pool;
    iterate_through_directory(path,file_count,lineCount,pool);
    EXPECT_EQ(file_count,0);
    EXPECT_EQ(lineCount.lines,0);
}

TEST_F(FileParserTest, NonEmptyDir)
{
    fs::path path("tests");
    lineCountData lineCount;
    uint file_count = -1;
    ThreadPool pool;
    int result=iterate_through_directory(path,file_count,lineCount,pool);
    EXPECT_EQ(file_count,3);
    EXPECT_EQ(lineCount.lines,7);
}

TEST_F(FileParserTest, DefaultThreadPool)
{
  ThreadPool pool;
  int defaultCount= std::thread::hardware_concurrency();
  EXPECT_EQ(pool.threadCount(),defaultCount);
}

TEST_F(FileParserTest, ZeroedThreadPool)
{
  ThreadPool pool(0);
  int defaultCount= std::thread::hardware_concurrency();
  EXPECT_EQ(pool.threadCount(),defaultCount);
}

TEST_F(FileParserTest, SingleThreadPool)
{
  ThreadPool pool(1);
  int defaultCount= std::thread::hardware_concurrency();
  EXPECT_EQ(pool.threadCount(),1);
}

TEST_F(FileParserTest, BigThreadPool)
{
  ThreadPool pool(10000);
  EXPECT_EQ(pool.threadCount(),10000);
}

TEST_F(FileParserTest, ThreadPoolJobQueue)
{
  ThreadPool pool(1);
  pool.queueFile("tests/empty_file.txt");

  EXPECT_EQ(pool.returnResult().lines,0);
}