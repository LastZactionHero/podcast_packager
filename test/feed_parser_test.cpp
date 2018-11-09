#include "../src/feed_parser.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>

namespace {
  const std::string sampleFeedFilename = "./test/fixtures/sample_feed.xml";

  TEST(FeedParser, Title) {
    FeedParser fp = FeedParser(sampleFeedFilename);

    EXPECT_EQ(fp.title(), "The Film Reroll");
  }
}