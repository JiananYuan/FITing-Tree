//
// Created by Jiananyuan on 2022/10/19.
//

#ifndef INDEX_HOMEWORK_SHRINKINGCONE_SEGMENTATION_H
#define INDEX_HOMEWORK_SHRINKINGCONE_SEGMENTATION_H

const double ERROR = 100;

struct Segment {
  double slope;
  int start;

  Segment(double _slope, int _start) {
    slope = _slope;
    start = _start;
  }
};

#endif //INDEX_HOMEWORK_SHRINKINGCONE_SEGMENTATION_H
