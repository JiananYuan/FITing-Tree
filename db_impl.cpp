//
// Created by Jiananyuan on 2022/10/19.
//

#include "db_impl.h"



int get(tree, int key) {
  seg = search_tree(tree.root, key);
  int val = search_segment(seg, key);
  return val;
}

int search_tree(node, int key) {
  int i = 0;
  while (key < node.keys[i]) {
    i = i + 1;
  }
  if (node.val[i].is_leaf()) {
    int j = 0;
    while (key < node.val[j]) {
      j = j + 1;
    }
    return node.val[j];
  }
  return search_tree(node, key);
}

int search_segment(seg, int key) {
  int pos = (key - seg.start) * seg.slope;
  return binary_search(seg.data, pos - ERROR, pos + ERROR);
}

void delta_insert(tree, int key) {
  seg = search_tree(tree.root, key);
  seg.buffer.insert(key);
  if (seg.buffer.is_full()) {
    segs = shrinkingcore_segmentation(seg.data, seg.buffer);
    for (auto s : segs) {
      tree.insert(s);
    }
    tree.remove(seg);
  }
}
