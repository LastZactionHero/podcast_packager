#ifndef SRC_FEED_H_
#define SRC_FEED_H_

#include <string>
#include <vector>
#include "./episode.h"

struct Feed {
  std::string url;
  std::vector<Episode> episodes;

  explicit Feed(const std::string &url)
    : url(url)
  {}
};

#endif  // SRC_FEED_H_