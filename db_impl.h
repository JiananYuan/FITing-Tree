//
// Created by Jiananyuan on 2022/10/19.
//

#include "bptree.h"
#include "config.h"

BPTree* fiting_tree = new BPTree;

State get(int x) {
  fiting_tree -> search(x);
}

State insert(int x) {
  fiting_tree -> delta_insert(x);
}

State construct() {
    fiting_tree->construct();
}
