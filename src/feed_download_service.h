#ifndef SRC_FEED_DOWNLOAD_SERVICE_H_
#define SRC_FEED_DOWNLOAD_SERVICE_H_

#include "./feed.h"
#include <string>

class FeedDownloadService {
 public:
  explicit FeedDownloadService(Feed *feed);
  bool download();

 private:
  Feed *feed;

  std::string filename();
};

#endif  // SRC_FEED_DOWNLOAD_SERVICE_H_
