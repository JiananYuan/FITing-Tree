//
// Created by Jiananyuan on 2022/10/19.
//

#include "shrinkingcone_segmentation.h"
#include <vector>

std::vector<Segment> shrinkingcore_segmentation(std::vector<int> keys, std::vector<int> buf) {
  if (buf.size() != 0) {
    keys.insert(keys.end(), buf.begin(), buf.end());
  }
  double sl_high = 1e9; // infinite
  double sl_low = 0;
  int origin_loc = 0;
  std::vector<Segment> segs;
  for (int i = 1; i < keys.size(); i += 1) {
    double k_up = keys[i] + ERROR;
    double l_low = keys[i] - ERROR;
    double max_bound = sl_high * keys[i];
    double min_bound = sl_low * keys[i];
    if (keys[i] >= min_bound && keys[i] <= max_bound) {
      sl_high = (k_up - keys[origin_loc]) / (i - origin_loc);
      sl_low = (k_low - keys[origin_loc]) / (i - origin_loc);
    }
    else {
      double slope = (keys[i - 1] - keys[origin_loc]) / (i - origin_loc);
      segs.emplace_back(Segment(slope, keys[origin_loc]));
      origin_loc = i;
      sl_high = 1e9; // infinite
      sl_low = 0;
    }
  }
  return segs;
}


