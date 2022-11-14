//
// Created by Jiananyuan on 2022/10/19.
//

#include "bptree.h"

BPTree* fiting_tree = new BPTree;

void get(int x) {
  fiting_tree -> search(x);
}

void insert(int x) {
  fiting_tree -> delta_insert(x);
}

void construct() {
    fiting_tree->construct();
}