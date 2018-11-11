#ifndef SRC_PREVIOUS_EPISODE_SERVICE_H
#define SRC_PREVIOUS_EPISODE_SERVICE_H

#include <set>
#include <string>
#include <vector>
#include "./episode.h"

class PreviousEpisodeService {
 public:
  explicit PreviousEpisodeService(const std::string filename);
  void markPreviouslyDownloaded(std::vector<Episode> *episodes);
  void appendPreviouslyDownloaded(const Episode &episode);

 private:
  std::string filename;
  std::set<std::string> urls;
};

#endif  // SRC_PREVIOUS_EPISODE_SERVICE_H