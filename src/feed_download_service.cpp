#include "./feed_download_service.h"

#include "./file_download_service.h"
#include "./feed_parser.h"

FeedDownloadService::FeedDownloadService(Feed *feed)
  : feed(feed) {}

bool FeedDownloadService::download() {
  FileDownloadService fds = FileDownloadService(
    feed->url,
    filename());

  if (!fds.download()) {
    return false;
  }

  FeedParser fp = FeedParser(filename());
  fp.episodes(&feed->episodes);

  remove(filename().c_str());

  return true;
}

std::string FeedDownloadService::filename() {
  return "file.xml";
}
