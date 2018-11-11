#ifndef SRC_EPISODE_H_
#define SRC_EPISODE_H_

#include <string>

struct Episode {
  std::string title;
  std::string pubDate;
  std::string url;
  bool downloaded;

  explicit Episode(
    const std::string title,
    const std::string pubDate,
    const std::string url) :
      title(title),
      pubDate(pubDate),
      url(url),
      downloaded(false)
  {}
};

#endif  // SRC_EPISODE_H_