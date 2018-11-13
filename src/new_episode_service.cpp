#include "./new_episode_service.h"
#include "./previous_episode_service.h"

NewEpisodeService::NewEpisodeService(std::vector<Feed> *feeds) : feeds(feeds) {}

std::vector<Episode> NewEpisodeService::newEpisodes(
  const std::string &filename) {
  std::vector<Episode> episodes;

  // Loop over each feed
  for (std::vector<Feed>::iterator itr = feeds->begin();
    itr != feeds->end();
    ++itr) {
    // Mark any previously downloaded episodes
    PreviousEpisodeService(filename).markPreviouslyDownloaded(&itr->episodes);

    // Add Episodes to the master list, stopping if we hit one that has
    // already been downloaded
    for (std::vector<Episode>::iterator eItr = itr->episodes.begin();
        eItr != itr->episodes.end();
        ++eItr) {
      if (eItr->downloaded) {
        break;
      }
      episodes.push_back(*eItr);
    }
  }

  return episodes;
}
