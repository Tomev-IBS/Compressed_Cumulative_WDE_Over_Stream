//
// Created by Tomev on 17/01/2021.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDSCALINGFUNCTION_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDSCALINGFUNCTION_H

#include <vector>

#include <boost/math/special_functions/daubechies_scaling.hpp>
#include <boost/math/filters/daubechies.hpp>

using boost::math::filters::daubechies_scaling_filter;

class TranslatedDilatedScalingFunction{
  public:
    static constexpr const int daubechies_wavelet_number_ = 5;

    TranslatedDilatedScalingFunction(const double &dilation, const double &translation, const int &grid_refinement = -2);
    double GetValue(const double &x) const;
    void UpdateIndices(const double &dilation, const double &translation);
    std::pair<double, double> GetOriginalScalingFunctionSupport();
    std::pair<double, double> GetTranslatedDilatedScalingFunctionSupport() const;
    std::array<double, 2 * daubechies_wavelet_number_> GetFilterCoefficients();

    double GetRegularity() const;

    boost::math::daubechies_scaling<double, daubechies_wavelet_number_> scaling_function_;

  protected:
    double dilation_index_; // j
    double translation_index_; // k

    // Regularities taken from Vidakovic book (page 85).
    // I use Sobolev ones.
    static const std::vector<double> regularities_;

};

#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDSCALINGFUNCTION_H
