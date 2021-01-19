//
// Created by Tomev on 19/01/2021.
//
// Implementation of
//

#include "WDE_Strategies/LinearWDEStrategy.h"

#include <cmath>
#include <numeric>

using std::inner_product;
using std::accumulate;

// TR TODO: Make separate file if it's used elsewhere.
/** Computes standard deviation estimator from given vector.
 * @brief Computes standard deviation estimator from given vector.
 * @param values - Vector of values.
 * @return Standard deviation estimator of values.
 */
double stDev(const vector<double> &values){

  if(values.size() < 1){
    return 0;
  }

  auto mean = accumulate(values.begin(), values.end(), 0.0) / values.size();
  auto squares_sum = inner_product(values.begin(), values.end(), values.begin(), 0.0);

  return sqrt(squares_sum / values.size() - pow(mean, 2));
}

LinearWDEStrategy::LinearWDEStrategy(const double &threshold)
    :  coefficient_threshold_(threshold) { }

/** Updates linear WDE data.
 * @brief Updates linear WDE data.
 * @param values_block - Block of new values which will be used during update process.
 */
void LinearWDEStrategy::UpdateWDEData(const vector<double> &values_block) {
  ComputeOptimalResolutionIndex(values_block);
  ComputeTranslations(values_block);
  ComputeEmpiricalScalingCoefficients(values_block);
}

/** Computes optimal resolition index.
 *
 * @brief Computes optimal resolition index.
 * @param values_block - Values from which resolution (dilation) index is computed.
 * @return Optimal resolution index.
 */
void LinearWDEStrategy::ComputeOptimalResolutionIndex(const vector<double> &values_block) {
    resolution_index_ = log2(values_block.size()) / 3.0 - 2.0 - log2(stDev(values_block));
}

/** Computes k_min and k_max (translation indices).
 * @brief Computes k_min and k_max (translation indices).
 * @param values_block - SORTED vector of values.
 */
void LinearWDEStrategy::ComputeTranslations(const vector<double> &values_block) {

  int support_min = TranslatedDilatedScalingFunction::original_function_support_min_;
  int support_max = TranslatedDilatedScalingFunction::original_function_support_max_;

  k_min_ = ceil(pow(2, resolution_index_) * values_block[0] - support_max);
  k_max_ = floor(pow(2, resolution_index_) * values_block[values_block.size() - 1] - support_min);
}

/** Computes most important (according to threshold) empirical scaling function coefficients.
 * @brief Computes most important (according to threshold) empirical scaling function coefficients.
 * @param values - Vector of values in the block.
 */
void LinearWDEStrategy::ComputeEmpiricalScalingCoefficients(const vector<double> &values) {

  empirical_scaling_coefficients_ = {};

  if(values.empty()){
    return;
  }

  for(int k = k_min_; k <= k_max_; ++k){

    double coefficient = 0;

    auto scaling_function = TranslatedDilatedScalingFunction(resolution_index_, k);

    for(auto val : values){
      coefficient += scaling_function.GetValue(val);
    }

    coefficient /= values.size();

    if(coefficient < coefficient_threshold_){
      EmpiricalCoefficientData data;
      data.coefficient_ = coefficient;
      data.j_ = resolution_index_;
      data.k_ = k;
      empirical_scaling_coefficients_.push_back(data);
    }
  }
}

/** Computes value of decomposed function in 1D point.
 * @brief Computes value of decomposed function in 1D point.
 * @param x - 1D point in which the value of function should be computed.
 * @return Value of DWT in x.
 */
double LinearWDEStrategy::GetValue(const double &x) const {
  double result = 0;

  auto scaling_function = TranslatedDilatedScalingFunction(resolution_index_, 0);

  for(auto data : empirical_scaling_coefficients_){
    scaling_function.UpdateIndices(data.j_, data.k_);
    result += data.coefficient_ * scaling_function.GetValue(x);
  }

  return result;
}






