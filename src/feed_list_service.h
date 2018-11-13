#ifndef SRC_FEED_LIST_SERVICE_H_
#define SRC_FEED_LIST_SERVICE_H_

#include <string>
#include <vector>
#include "./feed.h"

class FeedListService {
 public:
  explicit FeedListService(const std::string &filename);
  std::vector<Feed> *feeds();

 private:
  std::vector<Feed> feedsList;

  void readFeeds(const std::string &filename);
};

#endif  // SRC_FEED_LIST_SERVICE_H_