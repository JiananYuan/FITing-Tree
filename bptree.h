#include <vector>
#include "shrinkingcone_segmentation.h"
#include <algorithm>
#include <iostream>
#include "config.h"
using namespace std;

std::vector<int> underlying_data;

// BP node
class Node {
  bool IS_LEAF;
  int *key, size;
  Node **ptr;
  Segment **seg;
  friend class BPTree;

public:
    Node();
    ~Node();
};

// BP tree
class BPTree {
    Node *root;
    void insertInternal(int, Node *, Node *);
    Node *findParent(Node *, Node *);

public:
    BPTree();
    void search(int);
    void insert(int);
    void construct();
    void display(Node *cursor);
};

Node::Node() {
    size = 0;
  key = new int[config::MAX];
  ptr = new Node *[config::MAX + 1];
  seg = new Segment *[config::MAX + 1];
}

Node::~Node() {
    delete key;
    for (int i = 0; i < config::MAX + 1; i += 1) {
        delete ptr[i];
    }
    delete ptr;
}

BPTree::BPTree() {
  root = NULL;
}

// Search operation
void BPTree::search(int x) {
  if (root == NULL) {
    cout << "Tree is empty\n";
    // return State::FAIL;
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
    int i = 0;
    for (; i < cursor->size; i++) {
        if (i == cursor->size - 1 || (x >= cursor->key[i] && x < cursor->key[i + 1])) {
            cursor = cursor->ptr[i + 1];
            break;
        }
    }
    Segment *seg = cursor->seg[i + 1];
    int pos = seg->slope * (x - seg->start);
    int l_bound = max_double(pos - config::ERROR, 0);
    int r_bound = pos + config::ERROR;
    pos = std::lower_bound(seg->data.begin() + l_bound, seg->data.begin() + r_bound, x) - seg->data.begin();
    if (seg->data[pos] == x) {
    //   return State::SUCCESS;
        cout << "Found" << "\n";
    }
    if (seg->search_buffer(x) == x) {
        // return State::SUCCESS;
        cout << "Found" << "\n";
    }
  }
//   return State::FAIL;
    cout << "Not_Found" << "\n";
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
        if (cursor->size < config::MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        } else {
            Node *newLeaf = new Node;
            int virtualNode[config::MAX + 1];
            for (int i = 0; i < config::MAX; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (x > virtualNode[i] && i < config::MAX)
                i++;
            for (int j = config::MAX + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;
            cursor->size = (config::MAX + 1) / 2;
            newLeaf->size = config::MAX + 1 - (config::MAX + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[config::MAX];
            cursor->ptr[config::MAX] = NULL;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            } else {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

// Insert Operation
void BPTree::insertInternal(int x, Node *cursor, Node *child) {
    if (cursor->size < config::MAX) {
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
        int virtualKey[config::MAX + 1];
        Node *virtualPtr[config::MAX + 2];
        for (int i = 0; i < config::MAX; i++) {
            virtualKey[i] = cursor->key[i];
        }
        for (int i = 0; i < config::MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        while (x > virtualKey[i] && i < config::MAX)
            i++;
        for (int j = config::MAX + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        for (int j = config::MAX + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (config::MAX + 1) / 2;
        newInternal->size = config::MAX - (config::MAX + 1) / 2;
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

void BPTree::construct() {
    vector<int> _;
    vector<Segment> segs = shrinkingcore_segmentation(underlying_data, _);
    for (Segment seg : segs) {
        insert(seg.start);
    }
    display(root);
    for (Segment seg : segs) {
        Node *cursor = root;
        while (cursor->IS_LEAF == false) {
            for (int i = 0; i < cursor->size; i++) {
                if (seg.start < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        // 抵达叶子节点, 找到合适的指针, 使其指向下层的'线段节点'
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == seg.start) {
                cursor->seg[i + 1] = &seg;
            }
        }
    }
}

// Print the tree
void BPTree::display(Node *cursor) {
  if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i]);
      }
    }
  }
}

