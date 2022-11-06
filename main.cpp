//
// Created by yuanj on 2022/11/6.
//

#include <iostream>
#include "db_impl.h"
#include <chrono>
using namespace std;
using namespace chrono;

const int N = 10000000;

int main() {
    double totle_time = 0;
    for (int i = 0; i < N; i += 1) {
        auto st = system_clock::now();
        insert(i);
        auto en = system_clock::now();
        auto duration = duration_cast<microseconds>(en - st);
        totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    }
    cout << "write time: " << totle_time / N << "s\n";

    totle_time = 0;
    for (int i = 0; i < N; i += 1) {
        auto st = system_clock::now();
        get(i);
        auto en = system_clock::now();
        auto duration = duration_cast<microseconds>(en - st);
        totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    }
    cout << "read time: " << totle_time / N << "s\n";
    return 0;
}
