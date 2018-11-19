#include "./directory_status.h"
#include <glob.h>
#include <iostream>

DirectoryStatus::DirectoryStatus(const std::string &filename) :
  filename(filename),
  lastHasFiles(false) {
}

void DirectoryStatus::setFilesReadyCallback(
  std::function<void(bool)> callback) {
  filesReadyCallback = callback;
}

void DirectoryStatus::poll() {
  bool hasFiles = directoryHasFiles();

  // Only callback on change
  if (hasFiles == lastHasFiles) {
    return;
  }

  std::cout << "hasFiles: " << hasFiles << std::endl;
  lastHasFiles = hasFiles;
  filesReadyCallback(hasFiles);
}

bool DirectoryStatus::directoryHasFiles() {
  std::string pattern = filename + "/*";

  glob_t globResult;
  glob(pattern.c_str(), GLOB_TILDE, NULL, &globResult);

  return globResult.gl_pathc > 0;
}
