//
// Created by Tomev on 07/01/2021.
//

#include "CompressedCumulativeWaveletDensityEstimator.h"

#include <algorithm>

CompressedCumulativeWaveletDensityEstimator::CompressedCumulativeWaveletDensityEstimator(
    const unsigned int &maximal_number_of_empirical_coefficients, const double &weights_modifier_,
    WaveletDensityEstimator* (*wde_factory_method)(const vector<double> &values_block),
    const double &block_size)
  : maximal_number_of_empirical_coefficients_(maximal_number_of_empirical_coefficients),
    weights_modifier_(weights_modifier_), wde_factory_method_(wde_factory_method), block_size_(block_size) { }

void CompressedCumulativeWaveletDensityEstimator::UpdateEstimator(const vector<double> &values_block) {
  AddNewEstimatorFromBlock(values_block);
  DecomposeToTheSameResolution();
  UpdateWeights();
  ConvexMergeEstimators();
  // At this points there should be only one estimator.
  while(estimators_[0]->GetEmpiricalCoefficientsNumber() > maximal_number_of_empirical_coefficients_){
    estimators_[0]->LowerCoefficientsResolution();
  }
}

void CompressedCumulativeWaveletDensityEstimator::AddNewEstimatorFromBlock(vector<double> values_block) {
  estimators_.push_back(WDEPtr(wde_factory_method_(values_block)));
}

/** Computes value of CCWDE in given point.
 * @brief Computes value of CCWDE in given point.
 * @param x - Point in which values is estimated.
 * @return Value of CCWDE in current point.
 */
double CompressedCumulativeWaveletDensityEstimator::GetValue(const point &x) const {
  double result = 0;

  for(const auto & estimator : estimators_){
    result += estimator->GetValue(x[0]);
  }

  return result;
}

/** Decomposes all the estimators to lowest resolution of them all.
 * @brief Decomposes all the estimators to lowest resolution of them all.
 */
void CompressedCumulativeWaveletDensityEstimator::DecomposeToTheSameResolution() {
  int lowest_resolution = FindLowestResolution();

  for(auto & estimator : estimators_){
    while(estimator->GetResolutionIndex() < lowest_resolution){
      estimator->LowerCoefficientsResolution();
    }
  }
}

/** Finds lowest resolution among current estimators. All estimators will be decomposed to this resolution.
 * @brief Find lowest resolution among current estimators.
 * @return Lowest resolution index of current estimators.
 */
int CompressedCumulativeWaveletDensityEstimator::FindLowestResolution() const {
  int lowest_resolution = estimators_[0]->GetResolutionIndex();

  for(const auto & estimator : estimators_){
    if(estimator->GetResolutionIndex() < lowest_resolution){
      lowest_resolution = estimator->GetResolutionIndex();
    }
  }

  return lowest_resolution;
}

void CompressedCumulativeWaveletDensityEstimator::UpdateWeights() {
  if(estimators_.size() > 1){
    estimators_[0]->MultiplyWeight(1.0 - weights_modifier_);
    estimators_[1]->MultiplyWeight(weights_modifier_);
  }
}

void CompressedCumulativeWaveletDensityEstimator::ConvexMergeEstimators() {
  if(estimators_.size() < 2){
    return;
  }

  auto merged_estimator = estimators_[0]->Merge(estimators_[1].get());
  estimators_.clear();
  estimators_.push_back(WDEPtr(merged_estimator));
}




