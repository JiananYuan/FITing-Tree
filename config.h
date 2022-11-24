#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace config {
  const int FANOUT = 100;
  const int BUFFER_SIZE = 20 + 1;
  double ERROR = 100;
  const int C = 50;
  const int PERFORMANCE_FIRST = 0;
  const int STORAGE_FIRST = 1;
}

enum State {
  SUCCESS,
  FAIL
};

#endif
