#include "./feed_list_service.h"
#include <fstream>
#include <iostream>

FeedListService::FeedListService(const std::string &filename) {
  readFeeds(filename);
}

std::vector<Feed> *FeedListService::feeds() {
  return &feedsList;
}

void FeedListService::readFeeds(const std::string &filename) {
  std::ifstream infile(filename);
  if (infile) {
    std::string line;
    while (getline(infile, line)) {
      if(line.length() > 0) {
        feedsList.emplace_back(line);
      }
    }
  } else {
    std::cout << "Could not open file " << filename << " for reading.\n";
  }
}