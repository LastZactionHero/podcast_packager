#include <gtest/gtest.h>

#include "../src/feed_download_service.h"
#include "../src/feed.h"

namespace {
  TEST(FeedDownloadService, Download) {
    std::string url = "http://localhost:9494/sample_feed.xml";

    Feed feed(url);
    EXPECT_EQ(feed.episodes.size(), 0);  // Assumption: No episodes

    FeedDownloadService fds = FeedDownloadService(&feed);
    EXPECT_EQ(fds.download(), true);

    EXPECT_EQ(feed.episodes.size(), 46);  // Assumption: No episodes
  }
}