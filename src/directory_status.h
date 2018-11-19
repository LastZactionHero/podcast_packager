#ifndef SRC_DIRECTORY_STATUS_H_
#define SRC_DIRECTORY_STATUS_H_

#include <functional>
#include <string>

class DirectoryStatus {
 public:
  explicit DirectoryStatus(const std::string &filename);
  void setFilesReadyCallback(std::function<void(bool)> callback);
  void poll();

 protected:
  std::function<void(bool)> filesReadyCallback;
  const std::string &filename;

  bool directoryHasFiles();
  bool lastHasFiles;
};

#endif  // SRC_DIRECTORY_STATUS_H_
