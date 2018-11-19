#include "./usb_mass_storage_manager.h"
#include <string>
#include <iostream>

#define MAX_CMD_BUFFER 64
#define DEVICE_ID "sda2"
#define MOUNT_PATH "/media/usbstick/"
#define CMD_DEVICE_AVAILABLE "ls -la /dev | grep " DEVICE_ID
#define CMD_MOUNT "mount -t vfat -o rw /dev/" DEVICE_ID " " MOUNT_PATH
#define CMD_UNMOUNT "umount " MOUNT_PATH
#define CMD_COPY_FILES "mv ./downloads/*.mp3 " MOUNT_PATH "podcasts/"

UsbMassStorageManager::UsbMassStorageManager() :
  mounted(false) {}

void UsbMassStorageManager::poll() {
  if (deviceAvailable()) {
    mount();
  }
}

void UsbMassStorageManager::unmount() {
  std::cout << "unmounting" << std::endl;
  popen(CMD_UNMOUNT, "r");
  if (mountedCallback) {
    mountedCallback(false);
  }
}

void UsbMassStorageManager::copyFiles(std::function<void(void)> callback) {
  std::cout << "copying" << std::endl;
  popen(CMD_COPY_FILES, "r");
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
  std::cout << "mounting" << std::endl;
  popen(CMD_MOUNT, "r");

  if (mountedCallback) {
    mountedCallback(true);
  }
}
