#include "./updater.h"

#include <iostream>
#include <vector>
#include "./feed_list_service.h"
#include "./feed_download_service.h"
#include "./new_episode_service.h"
#include "./file_download_service.h"
#include "./previous_episode_service.h"

Updater::Updater() {}

void Updater::update() {
  FeedListService feedListService = FeedListService("./feeds.txt");
  std::vector<Feed> *feeds = feedListService.feeds();

  for (std::vector<Feed>::iterator itr = feeds->begin();
      itr != feeds->end();
      ++itr) {
    FeedDownloadService feedDownloadService = FeedDownloadService(&*itr);
    feedDownloadService.download();
  }

  NewEpisodeService newEpisodeService = NewEpisodeService(feeds);
  std::vector<Episode> downloadQueue =
    newEpisodeService.newEpisodes("./previous_episodes.txt");


  for (std::vector<Episode>::iterator itr = downloadQueue.begin();
       itr != downloadQueue.end();
       ++itr) {
    std::cout << itr->url << std::endl;

    FileDownloadService fds = FileDownloadService(
      itr->url,
      "./downloads/" + itr->title + ".mp3");
    fds.download();

    PreviousEpisodeService pes =
      PreviousEpisodeService("./previous_episodes.txt");
    pes.appendPreviouslyDownloaded(*itr);
  }
}
