//
// Created by Tomev on 17/01/2021.
//

#include "TranslatedDilatedWaveletFunction.h"
#include <cmath>

TranslatedDilatedWaveletFunction::TranslatedDilatedWaveletFunction(const double &dilation, const double &translation,
                                                                   const int &grid_refinement)
  : dilation_index_(dilation), translation_index_(translation) {
  scaling_function_ =
      boost::math::daubechies_scaling<double, daubechies_wavelet_number_>(grid_refinement);
}

double TranslatedDilatedWaveletFunction::GetValue(const double &x) const {
  return pow(2,  dilation_index_ / 2.0) * scaling_function_(pow(2, dilation_index_) * x - translation_index_);
}

void TranslatedDilatedWaveletFunction::UpdateIndices(const double &dilation, const double &translation) {
  dilation_index_ = dilation;
  translation_index_ = translation;
}

std::pair<double, double> TranslatedDilatedWaveletFunction::GetOriginalWaveletFunctionSupport() {
  return scaling_function_.support();
}

std::pair<double, double> TranslatedDilatedWaveletFunction::GetTranslatedDilatedWaveletFunctionSupport() const {
  auto scaling_function_support = scaling_function_.support();
  scaling_function_support.first = pow(2, -dilation_index_) * (scaling_function_support.first + translation_index_);
  scaling_function_support.second = pow(2, -dilation_index_) * (scaling_function_support.second + translation_index_);
  return scaling_function_support;
}

std::array<double, 2 * TranslatedDilatedWaveletFunction::daubechies_wavelet_number_> TranslatedDilatedWaveletFunction::GetFilterCoefficients() {
  return daubechies_wavelet_filter<double, daubechies_wavelet_number_>();
}


