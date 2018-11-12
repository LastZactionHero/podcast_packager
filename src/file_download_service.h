#ifndef SRC_FILE_DOWNLOAD_SERVICE_H_
#define SRC_FILE_DOWNLOAD_SERVICE_H_

#include <string>

class FileDownloadService {
 public:
  FileDownloadService(const std::string &url, const std::string &filename);
  bool download();

 private:
  std::string url;
  std::string filename;
};

#endif  // SRC_FILE_DOWNLOAD_SERVICE_H_