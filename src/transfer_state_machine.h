#ifndef SRC_TRANSFER_STATE_MACHINE_H_
#define SRC_TRANSFER_STATE_MACHINE_H_

#include "./mass_storage_manager.h"
#include "./directory_status.h"

class TransferStateMachine {
 public:
  enum State {
    IDLE,
    TRANSFERRING
  };

  enum StateFiles {
    NO_FILES,
    HAS_FILES
  };

  enum StateMassStorage {
    UNMOUNTED,
    MOUNTED
  };

  TransferStateMachine(
    DirectoryStatus *directoryStatus,
    MassStorageManager *massStorageManager);

  State getState();
  StateMassStorage getStateMassStorage();
  StateFiles getStateFiles();

 private:
  void startTransferIfReady();
  void transferComplete();
  void filesChanged(bool hasFiles);
  void massStorageMounted(bool mounted);

  DirectoryStatus *directoryStatus;
  MassStorageManager *massStorageManager;
  State state;
  StateFiles stateFiles;
  StateMassStorage stateMassStorage;
  bool running;
};

#endif  // SRC_TRANSFER_STATE_MACHINE_H_
