//
// Created by Tomev on 17/01/2021.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDWAVELETFUNCTION_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDWAVELETFUNCTION_H

#include <boost/math/special_functions/daubechies_wavelet.hpp>
#include <boost/math/filters/daubechies.hpp>

using boost::math::filters::daubechies_wavelet_filter;

class TranslatedDilatedWaveletFunction {
  public:
    static constexpr const int daubechies_wavelet_number_ = 5;

    TranslatedDilatedWaveletFunction(const double &dilation, const double &translation, const int &grid_refinement = -2);
    double GetValue(const double &x) const;
    void UpdateIndices(const double &dilation, const double &translation);
    std::pair<double, double> GetOriginalWaveletFunctionSupport();
    std::pair<double, double> GetTranslatedDilatedWaveletFunctionSupport() const;
    std::array<double, 2 * daubechies_wavelet_number_> GetFilterCoefficients();

    boost::math::daubechies_wavelet<double, daubechies_wavelet_number_> wavelet_function_;

  protected:
    double dilation_index_; // j
    double translation_index_; // k

};

#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDWAVELETFUNCTION_H
