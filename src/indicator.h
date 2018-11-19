#ifndef SRC_INDICATOR_H_
#define SRC_INDICATOR_H_

#include "./transfer_state_machine.h"

class Indicator {
 public:
  explicit Indicator(TransferStateMachine *tsm);
  virtual void update() = 0;

 protected:
  TransferStateMachine *tsm;
};

#endif  // SRC_INDICATOR_H_
