//
// Created by Tomev on 17/01/2021.
//

#include "TranslatedDilatedScalingFunction.h"
#include <cmath>

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

std::array<double, 2 * TranslatedDilatedScalingFunction::daubechies_wavelet_number_> TranslatedDilatedScalingFunction::GetFilterCoefficients() {
  return daubechies_scaling_filter<double, daubechies_wavelet_number_>();
}
