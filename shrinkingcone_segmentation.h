//
// Created by Jiananyuan on 2022/10/19.
//

#include <vector>
#include <algorithm>
#include "config.h"

struct Segment {
    double slope;
    int start;
    std::vector<int> data;

    Segment(double _slope, int _start, std::vector<int>& _data) {
        slope = _slope;
        start = _start;
        data.assign(_data.begin(), _data.end());
    }
};

std::vector<Segment> shrinkingcore_segmentation(std::vector<int> keys, std::vector<int> buf) {
  if (buf.size() != 0) {
    keys.insert(keys.end(), buf.begin(), buf.end());
    std::sort(keys.begin(), keys.end());
  }
  double sl_high = 1e9; // infinite
  double sl_low = 0;
  int origin_loc = 0;
  std::vector<Segment> segs;
  std::vector<int> data;
  data.push_back(keys[0]);
  for (int i = 1; i < keys.size(); i += 1) {
    double k_up = i + config::ERROR;
    double k_low = i - config::ERROR;
    double max_bound = sl_high * keys[i];
    double min_bound = sl_low * keys[i];
    if (i >= min_bound && i <= max_bound) {
      sl_high = (k_up - origin_loc) / (keys[i] - keys[origin_loc]);
      sl_low = (k_low - origin_loc) / (keys[i] - keys[origin_loc]);
      data.push_back(keys[i]);
      if (i == keys.size() - 1) {
          double slope = (i - origin_loc) / (keys[i] - keys[origin_loc]);
          segs.emplace_back(Segment(slope, keys[origin_loc], data));
      }
    }
    else {
      double slope = ((i - 1) - origin_loc) / (keys[i - 1] - keys[origin_loc]);
      segs.emplace_back(Segment(slope, keys[origin_loc], data));
      origin_loc = i;
      sl_high = 1e9;
      sl_low = 0;
      data.clear();
      data.push_back(i);
    }
  }
  return segs;
}
