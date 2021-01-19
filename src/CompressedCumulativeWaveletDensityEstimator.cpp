//
// Created by Tomev on 07/01/2021.
//

#include "CompressedCumulativeWaveletDensityEstimator.h"

#include <algorithm>
#include <iostream>

void CompressedCumulativeWaveletDensityEstimator::UpdateEstimator(const vector<double> &values_block) {
  CalculateBlockWDE(values_block);
}

void CompressedCumulativeWaveletDensityEstimator::CalculateBlockWDE(vector<double> values_block) {
  std::sort(values_block.begin(), values_block.end());

  for(auto val : values_block){
    std::cout << val << std::endl;
  }


}

double CompressedCumulativeWaveletDensityEstimator::GetValue(const vector<point> &x) const {
  return 0;
}


