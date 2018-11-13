#ifndef SRC_NEW_EPISODE_SERVICE_H_
#define SRC_NEW_EPISODE_SERVICE_H_

#include <string>
#include <vector>
#include "./feed.h"
#include "./episode.h"

class NewEpisodeService {
 public:
  explicit NewEpisodeService(std::vector<Feed> *feeds);
  std::vector<Episode> newEpisodes(const std::string &filename);

 private:
  std::vector<Feed> *feeds;
};

#endif  // SRC_NEW_EPISODE_SERVICE_H_