//
// Created by yuanj on 2022/11/6.
// 测量时延和index大小

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
#include <assert.h>

using namespace std;
using namespace chrono;
typedef long long ll;
vector<ll> under_data;

int main(int argc, char** argv) {
  assert(argc == 3 + 1);
  string PATH = string(argv[1]);
  int op = atoi(argv[2]);  // 0: 性能优先  1: 存储优先
  double req = atoi(argv[3]);  // 性能或存储限制

  cout << "[Stage 1]: 从外部文件读取数据..." << "\n";
  ifstream fp(PATH);
  string line;
  // getline(fp, line);
  while (getline(fp, line)) {
    istringstream readstr(line);
    string number;
    getline(readstr, number, ',');
    under_data.push_back(atoll(number.data()));
  }
  cout << "数据规模: " << under_data.size() << "\n\n";

  // 挑选e值
  // cout << "[Stage 2]: 使用Cost Model返回最佳e值..." << "\n";
  // config::ERROR = get_e(op, req, under_data);
  // assert(op == 0 || op == 1);
  // assert(config::ERROR == 10 || config::ERROR == 100 || config::ERROR == 1000);
  config::ERROR = 100;
  cout << "e值: " << config::ERROR << "\n\n";

  cout << "[Stage 3]: 建立FITing-tree..." << "\n\n";
  construct(under_data);
  cout << "索引大小" << getsize() << "\n\n";

  cout << "[Stage 4]: 写过程..." << "\n";
  double totle_time = 0;
  auto st = system_clock::now();
  for (int i = 100001; i <= 110000; i += 1) {
    insert(i);
  }
  auto en = system_clock::now();
  auto duration = duration_cast<microseconds>(en - st);
  totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
  cout << "写时延: " << totle_time / 10000 << "\n\n";

  totle_time = 0;
  cout << "[Stage 5]: 读过程..." << "\n";
  st = system_clock::now();
  for (int i = 0; i < 20000; i += 2) {
    get(i);
  }
  en = system_clock::now();
  duration = duration_cast<microseconds>(en - st);
  totle_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;
  cout << "读时延: " << totle_time / 10000 << "\n\n";
  return 0;
}
