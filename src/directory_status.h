#ifndef SRC_DIRECTORY_STATUS_H_
#define SRC_DIRECTORY_STATUS_H_

#include <functional>

class DirectoryStatus {
 public:
  void setFilesReadyCallback(std::function<void(bool)> callback);

 protected:
  std::function<void(bool)> filesReadyCallback;
};

#endif  // SRC_DIRECTORY_STATUS_H_