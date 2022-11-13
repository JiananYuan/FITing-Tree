//
// Created by Jiananyuan on 2022/10/19.
//

#include "bptree.h"

BPTree* fiting_tree = new BPTree;

State get(int x) {
  return fiting_tree -> search(x);
}

State insert(int x) {
  return fiting_tree -> insert(x);
}

void construct() {
    fiting_tree->construct();
}