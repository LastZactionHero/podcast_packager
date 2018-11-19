#include <gtest/gtest.h>
#include "../src/directory_status.h"
#include <fstream>

#define TEST_DOWNLOAD_DIR "test/downloads/"
#define TEST_DOWNLOAD_FILENAME TEST_DOWNLOAD_DIR "file.mp3"

void createFile() {
  std::ofstream outfile(TEST_DOWNLOAD_FILENAME);
  outfile << "test";
  outfile.close();
}

void removeFile() {
  remove(TEST_DOWNLOAD_FILENAME);
}

static int callbackCount = 0;
static bool callbackHasFiles = false;
void callback(bool hasFiles) {
  ++callbackCount;
  callbackHasFiles = hasFiles;
}

TEST(DirectoryStatus, Poll) {
  mkdir(TEST_DOWNLOAD_DIR, ACCESSPERMS);

  DirectoryStatus ds = DirectoryStatus(TEST_DOWNLOAD_DIR);
  ds.setFilesReadyCallback(
    std::bind(&callback,
    std::placeholders::_1));

  // Callback if directory has content
  createFile();
  ds.poll();
  EXPECT_EQ(callbackCount, 1);
  EXPECT_EQ(callbackHasFiles, true);

  // No callback if directory still has content
  ds.poll();
  EXPECT_EQ(callbackCount, 1);
  EXPECT_EQ(callbackHasFiles, true);


  // Callback if directory does not have content
  removeFile();
  ds.poll();
  EXPECT_EQ(callbackCount, 2);
  EXPECT_EQ(callbackHasFiles, false);

  // No callback is directory still does not have content
  ds.poll();
  EXPECT_EQ(callbackCount, 2);
  EXPECT_EQ(callbackHasFiles, false);

  // Callback if directory has content again
  createFile();
  ds.poll();
  EXPECT_EQ(callbackCount, 3);
  EXPECT_EQ(callbackHasFiles, true);

  removeFile();
  rmdir(TEST_DOWNLOAD_DIR);
}