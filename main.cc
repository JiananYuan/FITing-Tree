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

using namespace std;
using namespace chrono;
typedef long long ll;

// 性能优先保障
int performance_tradeoff() {
  const int e[] = {10, 100, 1000};
  double Lreq;
  int best_e = 0;
  int max_size = 99999999;
  for (int ei : e) {
    double latency = get_latency();
    if (latency < Lreq) {
      int size = fiting_tree -> calculate_size(fiting_tree->root);
      if (size < max_size) {
        max_size = size;
        best_e = ei;
      }
    }
  }
  return best_e;
}

// 存储优先保障
int size_tradeoff() {
  const int e[] = {10, 100, 1000};
  int Sreq;
  int best_e = 0;
  int min_latency = 9999999;
  for (int ei : e) {
    // TODO: 设计模式
    int size = fiting_tree -> calculate_size(fiting_tree->root);
    if (size < Sreq) {
      double latency = get_latency();
      if (latency < min_latency) {
        min_latency = latency;
        best_e = ei;
      }
    }
  }
  return best_e;
}

int main(int argc, char** argv) {
    string PATH;
    if (argc > 1) {
        PATH = string(argv[1]);
    }
    else {
        cout << "no input file" << "\n";
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

    construct();
    cout << "Finish Stage 2" << "\n";

    double totle_time = 0;
    auto st = system_clock::now();
    insert(1001);
    auto en = system_clock::now();
    auto duration = duration_cast<microseconds>(en - st);
    totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    cout << "insert latency: " << totle_time << "\n";
    cout << "Finish Stage 3" << "\n";
    totle_time = 0;

    st = system_clock::now();
    get(1001);
    en = system_clock::now();
    duration = duration_cast<microseconds>(en - st);
    totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
    cout << "read latency: " << totle_time << "\n";
    cout << "Finish Stage 4" << "\n";
    return 0;
}
