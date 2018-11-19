#ifndef SRC_TRANSFER_STATE_MACHINE_H_
#define SRC_TRANSFER_STATE_MACHINE_H_

#include "./mass_storage_manager.h"
#include "./directory_status.h"
#include <functional>

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

  void setUpdateCallback(std::function<void(void)> callback);

 private:
  void startTransferIfReady();
  void transferComplete();
  void filesChanged(bool hasFiles);
  void massStorageMounted(bool mounted);
  void postUpdate();

  DirectoryStatus *directoryStatus;
  MassStorageManager *massStorageManager;
  State state;
  StateFiles stateFiles;
  StateMassStorage stateMassStorage;

  std::function<void(void)> updateCallback;
};

#endif  // SRC_TRANSFER_STATE_MACHINE_H_
