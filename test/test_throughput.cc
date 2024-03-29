//
// Created by yuanj on 2022/11/6.
// 测量吞吐量

#include <iostream>
#include <chrono>
#include <random>
#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <fstream>
#include <vector>
#include <assert.h>
#include "../ATree/db_impl.h"
#include "../ATree/config.h"

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
  cout << "数据规模: " << under_data.size() << "\n";

  // 挑选e值
  // cout << "[Stage 2]: 使用Cost Model返回最佳e值..." << "\n";
  // config::ERROR = get_e(op, req, under_data);
  // assert(op == 0 || op == 1);
  // assert(config::ERROR == 10 || config::ERROR == 100 || config::ERROR == 1000);
  cout << "e值: " << config::ERROR << "\n";

  cout << "[Stage 3]: 建立FITing-tree..." << "\n";
  construct(under_data);

  default_random_engine e(255);
  uniform_int_distribution<uint64_t> uniform_dist_file(0, under_data.size() - 1);
  uniform_int_distribution<uint64_t> uniform_dist_file2(0, 1000000);
  double total_time = 0;
	ll cnt = 50000;
  cout << "[Stage 4]: 读过程..." << "\n";
  for (int i = 0; i < cnt; i += 1) {
    ll tk = uniform_dist_file(e);
    tk = under_data[tk];
		auto st = system_clock::now();
		get(tk);
		auto en = system_clock::now();
		auto duration = duration_cast<microseconds>(en - st);
		total_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;  // 单位: s
	}
  cout << "读吞吐量: " << cnt / total_time << " ops/sec \n";

  cout << "[Stage 5]: 写过程..." << "\n";
  total_time = 0;
	for (int i = 0; i < cnt; i += 1) {
    ll tk = uniform_dist_file2(e);
		auto st = system_clock::now();
		insert(tk);
		auto en = system_clock::now();
		auto duration = duration_cast<microseconds>(en - st);
		total_time += double(duration.count()) * microseconds::period::num / microseconds::period::den;  // 单位: s
	}
  cout << "写吞吐量: " << cnt / total_time << " ops/sec \n";
  return 0;
}
