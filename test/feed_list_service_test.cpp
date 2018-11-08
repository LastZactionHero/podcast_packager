#include <gtest/gtest.h>
#include "../src/feed_list_service.h"

#include <vector>

namespace {
  const char* sampleFeedsFilename = "./test/fixtures/sample_feeds.txt";

  TEST(FeedListService, Feeds) {
    // It returns a vector of Feeds, populated with URLs
    FeedListService fls = FeedListService(sampleFeedsFilename);
    const std::vector<Feed> &feedList = fls.feeds();

    EXPECT_EQ(feedList.size(), 2);

    EXPECT_EQ(feedList.at(0).url, "https://www.filmreroll.com/?feed=podcast");
    EXPECT_EQ(feedList.at(1).url, "https://feeds.megaphone.fm/FGM8688359539");
  }
}