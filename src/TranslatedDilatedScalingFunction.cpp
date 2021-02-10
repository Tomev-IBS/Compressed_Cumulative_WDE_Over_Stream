//
// Created by Tomev on 17/01/2021.
//

#include "TranslatedDilatedScalingFunction.h"
#include <cmath>

const std::vector<double> TranslatedDilatedScalingFunction::regularities_ = {0.5, 1.0, 1.415, 1.775, 2.096, 2.388, 2.658, 2.914, 3.161, 3.402};

TranslatedDilatedScalingFunction::TranslatedDilatedScalingFunction(const double &dilation, const double &translation,
                                                                   const int &grid_refinement)
  : dilation_index_(dilation), translation_index_(translation) {
  scaling_function_ =
      boost::math::daubechies_scaling<double, daubechies_wavelet_number_>(grid_refinement);
}

double TranslatedDilatedScalingFunction::GetValue(const double &x) const {
  return pow(2,  dilation_index_ / 2.0) * scaling_function_(pow(2, dilation_index_) * x - translation_index_);
}

void TranslatedDilatedScalingFunction::UpdateIndices(const double &dilation, const double &translation) {
  dilation_index_ = dilation;
  translation_index_ = translation;
}

std::pair<double, double> TranslatedDilatedScalingFunction::GetOriginalScalingFunctionSupport() {
  return scaling_function_.support();
}

std::pair<double, double> TranslatedDilatedScalingFunction::GetTranslatedDilatedScalingFunctionSupport() const {
  auto scaling_function_support = scaling_function_.support();
  scaling_function_support.first = pow(2, -dilation_index_) * (scaling_function_support.first + translation_index_);
  scaling_function_support.second = pow(2, -dilation_index_) * (scaling_function_support.second + translation_index_);
  return scaling_function_support;
}

std::array<double, 2 * TranslatedDilatedScalingFunction::daubechies_wavelet_number_> TranslatedDilatedScalingFunction::GetFilterCoefficients() {
  return daubechies_scaling_filter<double, daubechies_wavelet_number_>();
}

double TranslatedDilatedScalingFunction::GetRegularity() const {

  // If we can return pre-programmed values, do so.
  if(daubechies_wavelet_number_ - 1 < regularities_.size()){
    return regularities_[daubechies_wavelet_number_];
  }

  // If not return empirical formula from https://arxiv.org/abs/hep-ph/0101182
  return 0.2 * daubechies_wavelet_number_;
}


