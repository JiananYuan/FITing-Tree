//
// Created by yuanj on 2022/11/6.
//

#include <iostream>
#include "db_impl.h"
#include <chrono>
#include "config.h"
#include <random>
#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <fstream>
#include "bptree.h"
#include <assert.h>
#include <stdio.h>

using namespace std;
using namespace chrono;
typedef long long ll;

int main(int argc, char** argv) {
    string PATH;
    int op; // 0: 性能优先  1: 存储优先
    if (argc == 2) {
        PATH = string(argv[1]);
        op = atoi(argv[2]);
    }
    else {
        cout << "no necessary arguments" << "\n";
        exit(-1);
    }
    ifstream fp(PATH);
    string line;
    getline(fp, line);
    while (getline(fp, line)) {
        istringstream readstr(line);
        string number;
        getline(readstr, number, ',');
        underlying_data.push_back(atoll(number.data()));
    }
    cout << "Finish Stage 1" << "\n";

    // e选型
    config::ERROR = get_e(op);
    assert(op == 0 || op == 1);
    cout << "Finish Stage 2" << "\n";

    construct();
    cout << "Finish Stage 3" << "\n";

    double totle_time = 0;
    auto st = system_clock::now();
    insert(1001);
    auto en = system_clock::now();
    auto duration = duration_cast<microseconds>(en - st);
    totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    cout << "insert latency: " << totle_time << "\n";
    cout << "Finish Stage 4" << "\n";
    totle_time = 0;

    st = system_clock::now();
    get(1001);
    en = system_clock::now();
    duration = duration_cast<microseconds>(en - st);
    totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    cout << "read latency: " << totle_time << "\n";
    cout << "Finish Stage 5" << "\n";
    return 0;
}
