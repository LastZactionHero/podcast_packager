#include "./transfer_state_machine.h"
#include <unistd.h>

TransferStateMachine::TransferStateMachine(
  DirectoryStatus *directoryStatus,
  MassStorageManager *massStorageManager)
  : directoryStatus(directoryStatus),
  massStorageManager(massStorageManager),
  state(IDLE),
  stateFiles(NO_FILES),
  stateMassStorage(UNMOUNTED) {
  directoryStatus->setFilesReadyCallback(
    std::bind(&TransferStateMachine::filesChanged,
    this,
    std::placeholders::_1));
  massStorageManager->setMountedCallback(
    std::bind(&TransferStateMachine::massStorageMounted,
    this,
    std::placeholders::_1));
}

TransferStateMachine::State TransferStateMachine::getState() {
  return state;
}

TransferStateMachine::StateMassStorage
  TransferStateMachine::getStateMassStorage() {
  return stateMassStorage;
}

TransferStateMachine::StateFiles
  TransferStateMachine::getStateFiles() {
  return stateFiles;
}

void TransferStateMachine::filesChanged(bool hasFiles) {
  stateFiles = hasFiles ? HAS_FILES : NO_FILES;
  startTransferIfReady();
  postUpdate();
}

void TransferStateMachine::massStorageMounted(bool mounted) {
  stateMassStorage = mounted ? MOUNTED : UNMOUNTED;
  startTransferIfReady();
  postUpdate();
}

void TransferStateMachine::transferComplete() {
  if (TRANSFERRING == state) {
    state = IDLE;
    postUpdate();
  }
}

void TransferStateMachine::startTransferIfReady() {
  if (IDLE == state
      && MOUNTED == stateMassStorage
      && HAS_FILES == stateFiles) {
    state = TRANSFERRING;
    massStorageManager->copyFiles(
      std::bind(&TransferStateMachine::transferComplete, this));
  }
}

void TransferStateMachine::setUpdateCallback(
  std::function<void(void)> callback) {
  updateCallback = callback;
}

void TransferStateMachine::postUpdate() {
  if (updateCallback) {
    updateCallback();
  }
}