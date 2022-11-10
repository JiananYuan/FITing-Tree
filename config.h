#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace config {
    const int MAX = 100;
    const int BUFFER_SIZE = 20;
    const int BASE = 100;
    // const int BASE = 10000000;
    const int N = 1 * BASE;
    const double ERROR = 100;
}

enum State {
    SUCCESS,
    FAIL
};

#endif
