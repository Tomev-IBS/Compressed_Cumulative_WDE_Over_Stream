//
// Created by Tomev on 17/01/2021.
//

#include "TranslatedDilatedWaveletFunction.h"
#include <cmath>

TranslatedDilatedWaveletFunction::TranslatedDilatedWaveletFunction(const double &dilation, const double &translation,
                                                                   const int &grid_refinement)
  : dilation_index_(dilation), translation_index_(translation) {
  wavelet_function_ =
      boost::math::daubechies_wavelet<double, daubechies_wavelet_number_>(grid_refinement);
}

double TranslatedDilatedWaveletFunction::GetValue(const double &x) const {
  return pow(2,  dilation_index_ / 2.0) * wavelet_function_(pow(2, dilation_index_) * x - translation_index_);
}

void TranslatedDilatedWaveletFunction::UpdateIndices(const double &dilation, const double &translation) {
  dilation_index_ = dilation;
  translation_index_ = translation;
}

std::pair<double, double> TranslatedDilatedWaveletFunction::GetOriginalWaveletFunctionSupport() {
  return wavelet_function_.support();
}

std::pair<double, double> TranslatedDilatedWaveletFunction::GetTranslatedDilatedWaveletFunctionSupport() const {
  auto wavelet_function_support = wavelet_function_.support();
  wavelet_function_support.first = pow(2, -dilation_index_) * (wavelet_function_support.first + translation_index_);
  wavelet_function_support.second = pow(2, -dilation_index_) * (wavelet_function_support.second + translation_index_);
  return wavelet_function_support;
}

std::array<double, 2 * TranslatedDilatedWaveletFunction::daubechies_wavelet_number_> TranslatedDilatedWaveletFunction::GetFilterCoefficients() {
  return daubechies_wavelet_filter<double, daubechies_wavelet_number_>();
}


