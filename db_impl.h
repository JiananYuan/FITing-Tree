//
// Created by Jiananyuan on 2022/10/19.
//

#include "bptree.h"
#include "config.h"

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
