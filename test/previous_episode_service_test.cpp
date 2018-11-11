#include <gtest/gtest.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "../src/previous_episode_service.h"
#include "../src/episode.h"

namespace {
  TEST(PreviousEpisodeService, markPreviouslyDownloaded) {
    const std::string previousEpisodesFilename =
      "./test/fixtures/sample_previous_episodes.txt";

    PreviousEpisodeService pes(previousEpisodesFilename);

    std::vector<Episode> episodes;
    episodes.emplace_back(
      "title",
      "pubDate",
      "http://www.podcast.com/episode_1.mp3"); // in previous file
    episodes.emplace_back(
      "title",
      "pubDate",
      "http://www.podcast.com/episode_2.mp3"); // in previous file
    episodes.emplace_back(
      "title",
      "pubDate",
      "http://www.podcast.com/episode_3.mp3"); // not in previous file

    pes.markPreviouslyDownloaded(&episodes);

    EXPECT_EQ(episodes.at(0).downloaded, true);
    EXPECT_EQ(episodes.at(1).downloaded, true);
    EXPECT_EQ(episodes.at(2).downloaded, false);
  }

  TEST(PreviousEpisodeService, appendPreviouslyDownloaded) {
    std::string previousEpisodesFilename =
      "./test/fixtures/append_previous_episode.txt";
    Episode episodeA("", "", "http://www.podcast.com/episode10.mp3");
    Episode episodeB("", "", "http://www.podcast.com/episode11.mp3");

    PreviousEpisodeService pes(previousEpisodesFilename);
    pes.appendPreviouslyDownloaded(episodeA);
    pes.appendPreviouslyDownloaded(episodeB);

    std::ifstream infile(previousEpisodesFilename);
    std::string contents(
      (std::istreambuf_iterator<char>(infile)),
      std::istreambuf_iterator<char>());

    std::string expected = episodeA.url + "\n" + episodeB.url + "\n";

    EXPECT_EQ(contents, expected);

    remove(previousEpisodesFilename.c_str());
  }
}  // namespace
