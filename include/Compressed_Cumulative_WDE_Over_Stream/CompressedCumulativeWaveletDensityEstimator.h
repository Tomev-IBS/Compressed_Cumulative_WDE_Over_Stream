//
// Created by Tomev on 07/01/2021.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_COMPRESSEDCUMULATIVEWAVELETDENSITYESTIMATOR_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_COMPRESSEDCUMULATIVEWAVELETDENSITYESTIMATOR_H

#include "WaveletDensityEstimator.h"
#include <vector>

using std::vector;

typedef vector<double> point;

/**
 * @brief This class is an implementation of UNIVARIATE wavelet density estimator.
 */
class CompressedCumulativeWaveletDensityEstimator{
  public:
    CompressedCumulativeWaveletDensityEstimator(const unsigned int &maximal_number_of_empirical_coefficients,
                                                const double &weights_modifier_,
                                                WaveletDensityEstimator* (*wde_factory_method)(const vector<double> &values_block));
    void UpdateEstimator(const vector<double> &values_block); // TR TODO: Vector of some kind of points?
    double GetValue(const point &x) const; // TR TODO: This should have some kind of interface
  protected:

    WaveletDensityEstimator* (*wde_factory_method_)(const vector<double> &values_block);
    vector<WDEPtr> estimators = {};
    unsigned int maximal_number_of_empirical_coefficients_ = 0;
    double weights_modifier_ = 0.75; // omega

    void AddNewEstimatorFromBlock(vector<double> values_block);
    void DecomposeToTheSameResolution();
    int FindLowestResolution() const;
    void UpdateWeights();
    void ConvexMergeEstimators();
};

typedef CompressedCumulativeWaveletDensityEstimator CC_WDE;

#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_COMPRESSEDCUMULATIVEWAVELETDENSITYESTIMATOR_H
