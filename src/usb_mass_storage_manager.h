#ifndef SRC_USB_MASS_STORAGE_MANAGER_H
#define SRC_USB_MASS_STORAGE_MANAGER_H

#include "./mass_storage_manager.h"

class UsbMassStorageManager : public MassStorageManager {
 public:
  UsbMassStorageManager();
  void poll();
  void copyFiles(std::function<void(void)> callback);
  void unmount();

 private:
  bool deviceAvailable();
  void mount();

  bool readyToRemount;
  bool mounted;
};

#endif  // SRC_USB_MASS_STORAGE_MANAGER_H