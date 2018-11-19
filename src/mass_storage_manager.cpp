#include "./mass_storage_manager.h"

void MassStorageManager::setMountedCallback(
  std::function<void(bool)> callback) {
  mountedCallback = callback;
}
