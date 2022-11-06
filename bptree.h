#include <vector>
#include "shrinkingcone_segmentation.h"
#include "algorithm"
#include <iostream>
using namespace std;

const int MAX = 3;
const int BUFFER_SIZE = 20;

// BP node
class Node {
  bool IS_LEAF;
  int *key, size;
  Node **ptr;
  int start; // 起始key
  double slope;
  std::vector<int> data;
  std::vector<int> buffer;
  friend class BPTree;

public:
    Node();
    void insert_buffer(int);
    bool is_buffer_full();
};

// BP tree
class BPTree {
    Node *root;
    void insertInternal(int, Node *, Node *);
    Node *findParent(Node *, Node *);
    std::vector<int> data;

public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node *);
    Node *getRoot();
};

Node::Node() {
  key = new int[MAX];
  ptr = new Node *[MAX + 1];
}

BPTree::BPTree() {
  root = NULL;
}

// Search operation
void BPTree::search(int x) {
  if (root == NULL) {
    cout << "Tree is empty\n";
  } else {
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    // 进入到叶子节点中，使用Segment算法
    int pos = cursor->slope * (x - cursor->start);
    int l_bound = pos - ERROR;
    int r_bound = pos + ERROR;
    pos = std::lower_bound(data.begin() + l_bound, data.begin() + r_bound, x) - data.begin();
    if (data[pos] == x) {
      cout << "Found\n";
    }
    else {
      cout << "Not found\n";
    }
//    for (int i = 0; i < cursor->size; i++) {
//      if (cursor->key[i] == x) {
//        cout << "Found\n";
//        return;
//      }
//    }
//    cout << "Not found\n";
  }
}

void Node::insert_buffer(int key) {  // 1 2 4 5  <-- (3)
  int i = size - 1;
  while (i >= 0 && buffer[i] > key) {
    buffer[i + 1] = buffer[i];
    i -= 1;
  }
  buffer[i + 1] = key;
  size += 1;
}

bool Node::is_buffer_full() {
  return size == BUFFER_SIZE;
}

// Insert Operation
void BPTree::insert(int x) {
  if (root == NULL) {
    root = new Node;
    root->key[0] = x;
    root->IS_LEAF = true;
    root->size = 1;
  } else {
    Node *cursor = root;
    Node *parent;
    while (cursor->IS_LEAF == false) {
      parent = cursor;
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    // 抵达leaf nodes
    // cursor: Segment节点
    cursor->insert_buffer(x);
    if (cursor->is_buffer_full()) {
      vector<Segment> segs = shrinkingcore_segmentation(cursor->data, cursor->buffer);
      for (Segment seg : segs) {
        // tree.insert(seg)
        Node *newNode = new Node;
        newNode->slope = seg.slope;
        newNode->start = seg.start;
        newNode->key[0] = seg.start;
        newNode->IS_LEAF = true;
        insertInternal(seg.start, parent, newNode);
      }
      // tree.remove(cursor)
      delete cursor;
    }


//    if (cursor->size < MAX) {
//      int i = 0;
//      while (x > cursor->key[i] && i < cursor->size)
//        i++;
//      for (int j = cursor->size; j > i; j--) {
//        cursor->key[j] = cursor->key[j - 1];
//      }
//      cursor->key[i] = x;
//      cursor->size++;
//      cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
//      cursor->ptr[cursor->size - 1] = NULL;
//    } else {
//      Node *newLeaf = new Node;
//      int virtualNode[MAX + 1];
//      for (int i = 0; i < MAX; i++) {
//        virtualNode[i] = cursor->key[i];
//      }
//      int i = 0, j;
//      while (x > virtualNode[i] && i < MAX)
//        i++;
//      for (int j = MAX + 1; j > i; j--) {
//        virtualNode[j] = virtualNode[j - 1];
//      }
//      virtualNode[i] = x;
//      newLeaf->IS_LEAF = true;
//      cursor->size = (MAX + 1) / 2;
//      newLeaf->size = MAX + 1 - (MAX + 1) / 2;
//      cursor->ptr[cursor->size] = newLeaf;
//      newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
//      cursor->ptr[MAX] = NULL;
//      for (i = 0; i < cursor->size; i++) {
//        cursor->key[i] = virtualNode[i];
//      }
//      for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
//        newLeaf->key[i] = virtualNode[j];
//      }
//      if (cursor == root) {
//        Node *newRoot = new Node;
//        newRoot->key[0] = newLeaf->key[0];
//        newRoot->ptr[0] = cursor;
//        newRoot->ptr[1] = newLeaf;
//        newRoot->IS_LEAF = false;
//        newRoot->size = 1;
//        root = newRoot;
//      } else {
//        insertInternal(newLeaf->key[0], parent, newLeaf);
//      }
//    }
  }
}

// Insert Operation
void BPTree::insertInternal(int x, Node *cursor, Node *child) {
  if (cursor->size < MAX) {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--) {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--) {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  } else {
    Node *newInternal = new Node;
    int virtualKey[MAX + 1];
    Node *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++) {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX + 1; i++) {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX)
      i++;
    for (int j = MAX + 1; j > i; j--) {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root) {
      Node *newRoot = new Node;
      newRoot->key[0] = cursor->key[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    } else {
      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++) {
    if (cursor->ptr[i] == child) {
      parent = cursor;
      return parent;
    } else {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

// Get the root
Node *BPTree::getRoot() {
  return root;
}
