//
// Created by Jiananyuan on 2022/10/19.
//

#include <vector>
#include <algorithm>
#include "config.h"
typedef long long ll;

struct Segment {
    double slope;
    ll start;
    std::vector<int> data;
    std::vector<int> buf;

    Segment(double _slope, int _start, std::vector<int>& _data) {
        slope = _slope;
        start = _start;
        data.assign(_data.begin(), _data.end());
        buf.resize(config::BUFFER_SIZE);
    }

    void insert_buffer(int key) {  // 1 2 4 5  <-- (3)
        int i = buf.size() - 1;
        buf.push_back(0);
        while (i >= 0 && buf[i] > key) {
            buf[i + 1] = buf[i];
            i -= 1;
        }
        buf[i + 1] = key;
    }

    bool is_buffer_full() {
        return buf.size() == config::BUFFER_SIZE;
    }

    int search_buffer(int x) {
        if (buf.size() != 0) {
            int pos = std::distance(buf.begin(), lower_bound(buf.begin(), buf.end(), x));
            return buf[pos];
        }
        return -1;
    }

    ~Segment() {
      data.resize(0);
      buf.resize(0);
    }

};

double min_double(double d1, double d2) {
  if (d1 < d2) {
    return d1;
  }
  return d2;
}

double max_double(double d1, double d2) {
  if (d1 < d2) {
    return d2;
  }
  return d1;
}

std::vector<Segment> shrinkingcore_segmentation(std::vector<ll>& keys, std::vector<ll>& buf) {
  keys.insert(keys.end(), buf.begin(), buf.end());
  buf.resize(0);
  std::sort(keys.begin(), keys.end());
  double sl_high = 1e9; // infinite
  double sl_low = 0;
  int origin_loc = 0;
  std::vector<Segment> segs;
  std::vector<ll> data;
  data.push_back(keys[0]);
  for (int i = 1; i < keys.size(); i += 1) {
    double k_up = i + config::ERROR;
    double k_low = i - config::ERROR;
    double max_bound = sl_high * keys[i];
    double min_bound = sl_low * keys[i];
    if (i >= min_bound && i <= max_bound) {
      sl_high = min_double((k_up - origin_loc) / (keys[i] - keys[origin_loc]), sl_high);
      sl_low = max_double((k_low - origin_loc) / (keys[i] - keys[origin_loc]), sl_low);
      data.push_back(keys[i]);
      if (i == keys.size() - 1) {
          double slope = (i - origin_loc) / (keys[i] - keys[origin_loc]);
          segs.emplace_back(Segment(slope, keys[origin_loc], data));
          data.resize(0);
      }
    }
    else {
      double slope = 1.0 * ((i - 1) - origin_loc) / (keys[i - 1] - keys[origin_loc]);
      segs.emplace_back(Segment(slope, keys[origin_loc], data));
      origin_loc = i;
      sl_high = 1e9;
      sl_low = 0;
      data.clear();
      data.resize(0);
      data.push_back(keys[i]);
    }
  }
  if (!data.empty()) {
      segs.emplace_back(Segment(0, keys[origin_loc], data));
      data.resize(0);
  }
  for (int i = 0; i < segs.size(); i += 1) {
      Segment& seg = segs[i];
      std::cout << "seg" << i << ": " << seg.start << " slope: " << seg.slope << " data_range: (" << *(seg.data.begin()) << ", " << *(seg.data.end()) << ")" << "\n";
  }
  return segs;
}
