#ifndef SRC_MASS_STORAGE_MANAGER_H_
#define SRC_MASS_STORAGE_MANAGER_H_

#include <functional>

class MassStorageManager {
 public:
  void setMountedCallback(std::function<void(bool)> callback);
  virtual void copyFiles(std::function<void(void)> callback) = 0;
  virtual void unmount() = 0;

 protected:
  std::function<void(bool)> mountedCallback;

};

#endif  // SRC_MASS_STORAGE_MANAGER_H_
