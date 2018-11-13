#include <gtest/gtest.h>
#include "../src/new_episode_service.h"
#include "../src/feed.h"

namespace {
  TEST(NewEpisodeService, NewEpisodes) {
    // It filters to episodes that have not been previously downloaded
    std::vector<Feed> feeds;
    feeds.emplace_back("");

    Feed *feed = &feeds.at(0);
    feed->episodes.emplace_back("", "", "http://www.podcast.com/episode_4.mp3");  // New Episode
    feed->episodes.emplace_back("", "", "http://www.podcast.com/episode_3.mp3");  // New Episode
    feed->episodes.emplace_back("", "", "http://www.podcast.com/episode_2.mp3");  // Already downloaded
    feed->episodes.emplace_back("", "", "http://www.podcast.com/episode_1.mp3");  // Already downloaded
    feed->episodes.emplace_back("", "", "http://www.podcast.com/episode_5.mp3");  // Skipped, after an already downloaded

    NewEpisodeService nes = NewEpisodeService(&feeds);

    std::vector<Episode> newEpisodes = nes.newEpisodes("./test/fixtures/sample_previous_episodes.txt");
    EXPECT_EQ(newEpisodes.size(), 2);
  }
}