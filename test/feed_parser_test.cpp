#include "../src/feed_parser.h"
#include "../src/episode.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>

namespace {
  const std::string sampleFeedFilename = "./test/fixtures/sample_feed.xml";

  TEST(FeedParser, Title) {
    FeedParser fp = FeedParser(sampleFeedFilename);

    EXPECT_EQ(fp.title(), "The Film Reroll");
  }

  TEST(FeedParser, Episodes) {
    FeedParser fp = FeedParser(sampleFeedFilename);
    std::vector<Episode> episodes;

    fp.episodes(&episodes);

    EXPECT_EQ(episodes.size(), 46);

    EXPECT_EQ(episodes.at(0).title, "Ep 46: Friday the 13th: the Final Chapter (Part 1)");
    EXPECT_EQ(episodes.at(0).pubDate, "Wed, 24 Oct 2018 08:18:19 +0000");
    EXPECT_EQ(episodes.at(0).url, "http://feeds.soundcloud.com/stream/519071754-pauloquiros-film-reroll-ep-46-friday-the-13th-the-final-chapter-part-1.mp3");
  }
}