#include <iostream>
#include <unistd.h>

#include "./transfer_state_machine.h"

#include "./usb_mass_storage_manager.h"
#include "./directory_status.h"
#include "./transfer_state_machine.h"
#define DOWNLOAD_DIR "./downloads"

int main() {
  std::cout << "Transfer" << std::endl;

  UsbMassStorageManager msm = UsbMassStorageManager();
  DirectoryStatus ds = DirectoryStatus(DOWNLOAD_DIR);
  TransferStateMachine tsm = TransferStateMachine(&ds, &msm);

  while (true) {
    msm.poll();
    ds.poll();

    usleep(1 * 1000 * 1000);
  }

  return 0;
}
