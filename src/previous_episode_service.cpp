#include "./previous_episode_service.h"
#include <fstream>
#include <iostream>

PreviousEpisodeService::PreviousEpisodeService(const std::string filename) :
  filename(filename) {
  std::ifstream infile(filename);
  if (!infile) {
    std::ofstream outfile(filename);
    outfile.close();
  }

  std::string line;
  while (getline(infile, line)) {
    urls.insert(line);
  }
}

void PreviousEpisodeService::markPreviouslyDownloaded(
  std::vector<Episode> *episodes) {
  for (std::vector<Episode>::iterator it = episodes->begin();
    it != episodes->end();
    ++it) {
    if (urls.find(it->url) != urls.end()) {
      it->downloaded = true;
    }
  }
}

void PreviousEpisodeService::appendPreviouslyDownloaded(
  const Episode &episode) {
  std::ofstream outfile;
  outfile.open(filename, std::ios::out | std::ios::app);
  if (!outfile) {
    std::cout << "Could not open file " << filename << " for writing.\n";
  }

  outfile << episode.url << std::endl;

  outfile.close();
}
