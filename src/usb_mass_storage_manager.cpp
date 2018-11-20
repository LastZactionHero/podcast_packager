#include "./usb_mass_storage_manager.h"
#include <string>
#include <iostream>

#define MAX_CMD_BUFFER 64
// TODO: Handle sdb
#define DEVICE_ID "sda2"
#define MOUNT_PATH "/media/usbstick/"
#define CMD_DEVICE_AVAILABLE "ls -la /dev | grep " DEVICE_ID
#define CMD_MOUNT "mount -t vfat -o rw /dev/" DEVICE_ID " " MOUNT_PATH
#define CMD_UNMOUNT "umount " MOUNT_PATH
#define CMD_COPY_FILES "mv ./downloads/*.mp3 " MOUNT_PATH "podcasts"

UsbMassStorageManager::UsbMassStorageManager() :
  readyToRemount(true),
  mounted(false) {}

void UsbMassStorageManager::poll() {
  if (deviceAvailable()) {
    mount();
  } else if (!readyToRemount) {
    std::cout << "Device removed, ready to remount" << std::endl;
    readyToRemount = true;
  } else if (mounted) {
    unmount();
  }

  // TODO: Unmount if removed
}

void UsbMassStorageManager::unmount() {
  std::cout << "unmounting" << std::endl;
  system(CMD_UNMOUNT);
  mounted = false;

  if (mountedCallback) {
    mountedCallback(false);
  }
}

void UsbMassStorageManager::copyFiles(std::function<void(void)> callback) {
  std::cout << "copying" << std::endl;
  std::cout << CMD_COPY_FILES << std::endl;
  system(CMD_COPY_FILES);
  copyCallback = callback;
}

bool UsbMassStorageManager::deviceAvailable() {
  std::string data;
  char buffer[MAX_CMD_BUFFER];

  FILE *stream = popen(CMD_DEVICE_AVAILABLE, "r");
  if (stream) {
    while (!feof(stream)) {
      if (fgets(buffer, MAX_CMD_BUFFER, stream) != NULL) {
        data.append(buffer);
      }
    }
    pclose(stream);
  }

  return data.length() > 0;
}

void UsbMassStorageManager::mount() {
  if (!readyToRemount) {
    return;
  }

  std::cout << "mounting" << std::endl;
  system(CMD_MOUNT);
  readyToRemount = false;
  mounted = true;

  if (mountedCallback) {
    mountedCallback(true);
  }
}
