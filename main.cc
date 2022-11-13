//
// Created by yuanj on 2022/11/6.
//

#include <iostream>
#include "db_impl.h"
#include <chrono>
#include "config.h"
#include <random>
#include <stdlib.h>
using namespace std;
using namespace chrono;

int main() {
    int k = 100;
    srand((unsigned)time(nullptr));
    for (int i = 1; i <= config::N; i += 1) {
        if (i % (config::N / 10) == 0) {
            k -= 9; // Segment-10%
        }
        underlying_data.push_back(k * i);  // 添加扰动
    }
    construct();

    double totle_time = 0;
    // for (int i = 0; i < config::N; i += 1) {
    //     auto st = system_clock::now();
    //     State s = insert(i);
    //     auto en = system_clock::now();
    //     auto duration = duration_cast<microseconds>(en - st);
    //     totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    //     if (s == State::SUCCESS) cout << "SUCCESS" << "\n";
    //     else                     cout << "FAIL" << "\n";
    // }
    // cout << "write time: " << totle_time / config::N << "s\n";

//    totle_time = 0;
//    for (int i = 0; i < config::N; i += 1) {
//        auto st = system_clock::now();
//        // State s = get(i);
//        get(i);
//        auto en = system_clock::now();
//        auto duration = duration_cast<microseconds>(en - st);
//        totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
//        // if (s == State::SUCCESS) cout << "FOUND" << "\n";
//        // else                     cout << "NOT FOUND" << "\n";
//    }
//    cout << "read time: " << totle_time / config::N << "s\n";
    get(100);
    return 0;
}
