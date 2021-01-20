//
// Created by Tomev on 07/01/2021.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_COMPRESSEDCUMULATIVEWAVELETDENSITYESTIMATOR_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_COMPRESSEDCUMULATIVEWAVELETDENSITYESTIMATOR_H

#include "WDE_Strategies/WDEStrategy.h"
#include <vector>

using std::vector;

typedef vector<double> point;

/**
 * @brief This class is an implementation of UNIVARIATE wavelet density estimator.
 */
class CompressedCumulativeWaveletDensityEstimator{
  public:
    CompressedCumulativeWaveletDensityEstimator() = default;
    void UpdateEstimator(const vector<double> &values_block); // TR TODO: Vector of some kind of points?
    double GetValue(const vector<point> &x) const; // TR TODO: This should have some kind of interface
  protected:
    void CalculateBlockWDE(vector<double> values_block);

    vector<WDEStrategy> WDE_Blocks = {};

};

typedef CompressedCumulativeWaveletDensityEstimator CC_WDE;

#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_COMPRESSEDCUMULATIVEWAVELETDENSITYESTIMATOR_H
