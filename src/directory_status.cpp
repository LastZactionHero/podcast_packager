#include "./directory_status.h"

void DirectoryStatus::setFilesReadyCallback(
  std::function<void(bool)> callback) {
  filesReadyCallback = callback;
}
