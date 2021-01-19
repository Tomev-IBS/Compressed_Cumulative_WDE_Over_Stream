//
// Created by Tomev on 17/01/2021.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDSCALINGFUNCTION_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDSCALINGFUNCTION_H

#include <boost/math/special_functions/daubechies_scaling.hpp>

class TranslatedDilatedScalingFunction{
  public:
    TranslatedDilatedScalingFunction(const double &dilation, const double &translation);
    double GetValue(const double &x) const;
    void UpdateIndices(const double &dilation, const double &translation);

    static constexpr const int original_function_support_min_ = 0;
    static constexpr const int original_function_support_max_ = 6;

  protected:
    double dilation_index_; // j
    double translation_index_; // k
    static constexpr const int daubechies_wavelet_number_ = 5;
    boost::math::daubechies_scaling<double, daubechies_wavelet_number_> scaling_function_;
};

#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_TRANSLATEDDILATEDSCALINGFUNCTION_H
