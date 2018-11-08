#ifndef SRC_FEED_H_
#define SRC_FEED_H_

#include <string>

struct Feed {
  std::string url;

  explicit Feed(const std::string &url)
    : url(url)
  {}
};

#endif  // SRC_FEED_H_