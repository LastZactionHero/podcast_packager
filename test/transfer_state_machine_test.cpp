#include <gtest/gtest.h>
#include "../src/transfer_state_machine.h"
#include "../src/mass_storage_manager.h"
#include "../src/directory_status.h"

class DummyMassStorageManager : public MassStorageManager {
 public:
  DummyMassStorageManager() : unmounted(false) {}

  void unmount() {
    unmounted = true;
  }

  void copyFiles(std::function<void(void)> callback) {
    copyCallback = callback;
  }

  void dummyMassStorageMounted(bool mounted) {
    if (mountedCallback) {
      mountedCallback(mounted);
    }
  }

  void dummyCopyCallback() {
    copyCallback();
  }

  bool unmounted;

 private:
  std::function<void(void)> copyCallback;
};

class DummyDirectoryStatus : public DirectoryStatus {
 public:
  DummyDirectoryStatus() : DirectoryStatus("") {
  }

  void dummyFilesReady(bool ready) {
    if (filesReadyCallback) {
      filesReadyCallback(ready);
    }
  }
};

namespace {
  // Test transitions correctly in response to events
  TEST(TransferStateMachine, Tranisition) {
    DummyDirectoryStatus dds = DummyDirectoryStatus();
    DummyMassStorageManager dmsm = DummyMassStorageManager();

    TransferStateMachine tsm = TransferStateMachine(&dds, &dmsm);

    EXPECT_EQ(dmsm.unmounted, false);  // Assumption

    // Initializes to IDLE, UNMOUNTED, NO_FILES
    EXPECT_EQ(tsm.getState(), TransferStateMachine::State::IDLE);
    EXPECT_EQ(tsm.getStateFiles(), TransferStateMachine::StateFiles::NO_FILES);
    EXPECT_EQ(tsm.getStateMassStorage(),
      TransferStateMachine::StateMassStorage::UNMOUNTED);

    // Files detected updates state
    dds.dummyFilesReady(true);
    EXPECT_EQ(tsm.getStateFiles(), TransferStateMachine::StateFiles::HAS_FILES);
    dds.dummyFilesReady(false);
    EXPECT_EQ(tsm.getStateFiles(), TransferStateMachine::StateFiles::NO_FILES);

    // Mass storage mount updates state
    dmsm.dummyMassStorageMounted(true);
    EXPECT_EQ(tsm.getStateMassStorage(),
      TransferStateMachine::StateMassStorage::MOUNTED);
    dmsm.dummyMassStorageMounted(false);
    EXPECT_EQ(tsm.getStateMassStorage(),
      TransferStateMachine::StateMassStorage::UNMOUNTED);

    // Files detected + Mass storage mount triggers transfer
    EXPECT_EQ(tsm.getState(), TransferStateMachine::State::IDLE);  // Assumption
    dmsm.dummyMassStorageMounted(true);
    dds.dummyFilesReady(true);
    EXPECT_EQ(tsm.getState(), TransferStateMachine::State::TRANSFERRING);

    // Finishing the copy process triggers return to idle
    dmsm.dummyCopyCallback();
    EXPECT_EQ(tsm.getState(), TransferStateMachine::State::IDLE);
  }

  // Test update callback is called on transitions
  TEST(TransferStateMachine, TransitionCallback) {
    DummyDirectoryStatus dds = DummyDirectoryStatus();
    DummyMassStorageManager dmsm = DummyMassStorageManager();

    static int callbackCount = 0;
    auto updateCallback = []() {
      ++callbackCount;
      return;
    };

    TransferStateMachine tsm = TransferStateMachine(&dds, &dmsm);
    tsm.setUpdateCallback(updateCallback);

    // Triggers on mass storage mount
    dmsm.dummyMassStorageMounted(true);
    EXPECT_EQ(callbackCount, 1);

    // Triggers on mass storage mount
    dds.dummyFilesReady(true);
    EXPECT_EQ(callbackCount, 2);

    // Triggers on transfer complete
    dmsm.dummyCopyCallback();
    EXPECT_EQ(callbackCount, 3);
  }
}
