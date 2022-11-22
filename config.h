#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace config {
    const int MAX = 100;
    const int BUFFER_SIZE = 20 + 1;
    const int BASE = 1000;
    // const int BASE = 10000000;
    const int N = 1 * BASE;
    const double ERROR = 100;
    const int C = 50; // TODO: really 50?
}

enum State {
    SUCCESS,
    FAIL
};

#endif
