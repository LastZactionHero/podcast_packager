#include <gtest/gtest.h>
#include "./constants.h"
#include "../src/file_download_service.h"
#include <fstream>
#include <string>

TEST(FileDownloadService, Download) {
  std::string url = std::string(TEST_SERVER_HOST) + "sample_feed.xml";
  std::string filename = "./test/fixtures/out.xml";

  FileDownloadService fds = FileDownloadService(url, filename);
  EXPECT_EQ(fds.download(), true);

  std::ifstream infile(filename);
  std::string line;
  getline(infile, line);
  EXPECT_EQ(line, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");

  remove(filename.c_str());
}

TEST(FileDownloadService, DownloadError) {
  std::string url = std::string(TEST_SERVER_HOST) + "not_a_real_file";
  std::string filename = "./test/fixtures/out.xml";

  FileDownloadService fds = FileDownloadService(url, filename);
  EXPECT_EQ(fds.download(), false);

  std::ifstream infile(filename);
  if (infile) {
    EXPECT_EQ(false, true);
  }
  // EXPECT_EQ(infile, NULL);
  // std::string line;
  // getline(infile, line);
  // EXPECT_EQ(line, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");

  remove(filename.c_str());
}
