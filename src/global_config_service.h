#ifndef SRC_GLOBAL_CONFIG_SERVICE_H_
#define SRC_GLOBAL_CONFIG_SERVICE_H_

#include <string>
#include <map>

// Maintains config settings parsed from a config file
class GlobalConfigService {
 public:
  explicit GlobalConfigService(const std::string &filename);

  // Gets the config value as a string, empty string if not found
  const std::string get(const std::string &key);

  // Gets the config value as an integer, zero if not found or non-convertable
  const int getInt(const std::string &key);

  // Gets the config value as a float, zero if not found or non-convertable
  const float getFloat(const std::string &key);

 private:
  std::map<std::string, std::string> configMap;

  // Reads the config file to the map
  void readConfig(const std::string &filename);

  // Parses and individual config file line and save to the map
  void parseLine(const std::string &line);
};

#endif  // SRC_GLOBAL_CONFIG_SERVICE_H_
