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
#include <vector>
#include "bptree.h"
#include <assert.h>

using namespace std;
using namespace chrono;
typedef long long ll;
vector<ll> under_data;

int main(int argc, char** argv) {
    assert(argc == 2);
    string PATH;
    int op;  // 0: 性能优先  1: 存储优先
    double req;  // 性能或存储限制
    if (argc == 2) {
        PATH = string(argv[1]);
        op = atoi(argv[2]);
        req = atoi(argv[3]);
    }
    else {
        cout << "no necessary arguments" << "\n";
        exit(-1);
    }

    cout << "[Stage 1]: 从外部文件读取数据..." << "\n";
    ifstream fp(PATH);
    string line;
    getline(fp, line);
    while (getline(fp, line)) {
        istringstream readstr(line);
        string number;
        getline(readstr, number, ',');
        under_data.push_back(atoll(number.data()));
    }

    // 挑选e值
    cout << "[Stage 2]: 使用Cost Model返回最佳e值..." << "\n";
    config::ERROR = get_e(op, req, under_data);
    assert(op == 0 || op == 1);
    assert(config::ERROR == 10 || config::ERROR == 100 || config::ERROR == 1000);

    cout << "[Stage 3]: 建立FITing-tree..." << "\n";
    construct(under_data);

    cout << "[Stage 4]: 写过程..." << "\n";
    double totle_time = 0;
    auto st = system_clock::now();
    insert(1001);
    auto en = system_clock::now();
    auto duration = duration_cast<microseconds>(en - st);
    totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    cout << "insert latency: " << totle_time << "\n";
    totle_time = 0;

    cout << "[Stage 5]: 读过程..." << "\n";
    st = system_clock::now();
    get(1001);
    en = system_clock::now();
    duration = duration_cast<microseconds>(en - st);
    totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    cout << "read latency: " << totle_time << "\n";
    return 0;
}
