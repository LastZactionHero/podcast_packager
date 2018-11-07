#include <string>

class GlobalConfigService {
  public:
    GlobalConfigService(const std::string &aConfigFilename);
    int doAThing();

  private:
    std::string configFilename;
};

GlobalConfigService::GlobalConfigService(const std::string &aConfigFilename) {
  configFilename = aConfigFilename;
}

int GlobalConfigService::doAThing() {
  return 1;
}