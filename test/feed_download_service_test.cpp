#include <gtest/gtest.h>
#include "./constants.h"
#include "../src/feed_download_service.h"
#include "../src/feed.h"

namespace {
  TEST(FeedDownloadService, Download) {
    std::string url = std::string(TEST_SERVER_HOST) + "sample_feed.xml";

    Feed feed(url);
    EXPECT_EQ(feed.episodes.size(), 0);  // Assumption: No episodes

    FeedDownloadService fds = FeedDownloadService(&feed);
    EXPECT_EQ(fds.download(), true);

    EXPECT_EQ(feed.episodes.size(), 46);  // Assumption: No episodes
  }
}