//
// Created by Tomev on 19/01/2021.
//
// Header file for Linear Wavelet Density Estimation Strategy. It's meant for 1D data.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_LINEARWDESTRATEGY_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_LINEARWDESTRATEGY_H

#include "WDEStrategy.h"
#include "TranslatedDilatedScalingFunction.h"

#include <vector>

using std::vector;

class LinearWDEStrategy : public WDEStrategy{
  public:
    explicit LinearWDEStrategy(const double &threshold = 1e-5);
    void UpdateWDEData(const vector<double> &values_block) override;
    double GetValue(const double &x) const override;
  private:

    int resolution_index_ = 0;
    int k_min_ = 0;
    int k_max_ = 0;
    vector<EmpiricalCoefficientData> empirical_scaling_coefficients_ = {};

    double coefficient_threshold_ = 1e-5; // Denotes if the coefficient should be included.

    void ComputeOptimalResolutionIndex(const vector<double> &values_block);
    void ComputeTranslations(const vector<double> &values_block);
    void ComputeEmpiricalScalingCoefficients(const vector<double> &values);

};

#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_LINEARWDESTRATEGY_H
