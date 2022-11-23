//
// Created by Jiananyuan on 2022/10/19.
//

#include "bptree.h"
#include "config.h"
#include <climits.h>
typedef long long ll;
BPTree* fiting_tree = new BPTree;

State get(int x) {
  return fiting_tree -> search(x);
}

State insert(int x) {
  return fiting_tree -> delta_insert(x);
}

State construct() {
    return fiting_tree->construct();
}

const int e[] = {10, 100, 1000};

// 性能优先保障
int performance_tradeoff(double Lreq) {
    int best_e = 0;
    int min_size = INT_MAX;
    for (int ei : e) {
        double latency = get_latency();
        if (latency < Lreq) {
            int size = fiting_tree -> calculate_size(fiting_tree->root);
            if (size < min_size) {
                min_size = size;
                best_e = ei;
            }
        }
    }
    return best_e;
}

// 存储优先保障
int size_tradeoff(double Sreq) {
    int best_e = 0;
    int min_latency = INT_MAX;
    for (int ei : e) {
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

int get_e(int op) {
    if (op == config::PERFORMANCE_FIRST) {

    }
    else if (op == config::STORAGE_FIRST) {

    }
}
