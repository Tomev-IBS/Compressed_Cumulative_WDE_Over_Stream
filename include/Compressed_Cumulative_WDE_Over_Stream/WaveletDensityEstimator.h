//
// Created by Tomev on 19/01/2021.
//
// This file contains an interface for WDE strategy implementation.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_WAVELETDENSITYESTIMATOR_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_WAVELETDENSITYESTIMATOR_H

#include <vector>
#include <memory>

using std::vector;

struct EmpiricalCoefficientData{
  double coefficient_ = 0;
  int j_ = 0; // Dilation / Resolution index
  int k_ = 0; // Translation index

  bool operator >(const EmpiricalCoefficientData &other_coefficient) const {
    return this->coefficient_ > other_coefficient.coefficient_;
  }

  bool operator <(const EmpiricalCoefficientData &other_coefficient) const {
    return this->coefficient_ < other_coefficient.coefficient_;
  }
};

class WaveletDensityEstimator{
  public:
    virtual double GetValue(const double &x) const = 0;

    virtual void UpdateWDEData(const vector<double> &values) = 0;
    virtual void RemoveSmallestWaveletCoefficients(const unsigned int &number_of_coefficients = 0) = 0;
    virtual void LowerCoefficientsResolution() = 0;

    virtual int GetResolutionIndex() const = 0;
    virtual vector<EmpiricalCoefficientData> GetEmpiricalScalingCoefficients() const = 0;
    virtual vector<EmpiricalCoefficientData> GetEmpiricalWaveletCoefficients() const = 0;
    virtual unsigned int GetEmpiricalCoefficientsNumber() const = 0;
    virtual unsigned int GetEmpiricalScalingCoefficientsNumber() const = 0;
    virtual unsigned int GetEmpiricalWaveletCoefficientsNumber() const = 0;

    virtual double GetWeight() const = 0;
    virtual void SetWeight(const double &new_weight) = 0;
    virtual void MultiplyWeight(const double &multiplier) = 0;

    virtual WaveletDensityEstimator* Merge(WaveletDensityEstimator *other_wde) const = 0;
};

typedef std::shared_ptr<WaveletDensityEstimator> WDEPtr;

#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_WAVELETDENSITYESTIMATOR_H
