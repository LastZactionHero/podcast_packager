#include "./global_config_service.h"

#include <fstream>
#include <iostream>

GlobalConfigService::GlobalConfigService(const std::string &filename) {
  readConfig(filename);
}

const std::string GlobalConfigService::get(const std::string &key) {
  return configMap[key];
}

const int GlobalConfigService::getInt(const std::string &key) {
  const std::string &valueStr = get(key);

  try {
    return std::stoi(valueStr);
  } catch (const std::invalid_argument& ia) {
  }
  return 0;
}

const float GlobalConfigService::getFloat(const std::string &key) {
  const std::string &valueStr = get(key);

  try {
    return std::stof(valueStr);
  } catch (const std::invalid_argument& ia) {
  }
  return 0;
}

void GlobalConfigService::readConfig(const std::string &filename) {
  std::ifstream infile(filename);
  if (infile) {
    std::string line;
    while (getline(infile, line)) {
      parseLine(line);
    }
  } else {
    std::cout << "Could not open file " << filename << " for reading.\n";
  }
}

void GlobalConfigService::parseLine(const std::string &line) {
  // Skip blank lines and comments
  if (line.length() == 0 || '#' == line[0]) {
    return;
  }

  // Split the line into key/value
  const std::string delimiter = "=";
  int delimiterPosn = line.find(delimiter);
  std::string key = line.substr(0, delimiterPosn);
  std::string value = line.substr(delimiterPosn + 1, line.length() - 1);

  // Add to the map
  configMap.insert(std::pair<std::string, std::string>(key, value));
}
