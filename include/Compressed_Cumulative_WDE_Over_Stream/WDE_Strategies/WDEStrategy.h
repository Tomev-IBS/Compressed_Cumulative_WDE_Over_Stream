//
// Created by Tomev on 19/01/2021.
//
// This file contains an interface for WDE strategy implementation.
//

#ifndef COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_WDESTRATEGY_H
#define COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_WDESTRATEGY_H

#include <vector>

using std::vector;

struct EmpiricalCoefficientData{
  double coefficient_ = 0;
  int j_ = 0; // Dilation / Resolution index
  int k_ = 0; // Translation index
};

class WDEStrategy{
  public:
    virtual void UpdateWDEData(const vector<double> &values) = 0;
    virtual void LowerResolution() = 0;
    virtual double GetValue(const double &x) const = 0;
    virtual int GetResolutionIndex() const = 0;
    virtual void MultiplyWeight(const double &multiplicator) = 0;
};


#endif //COMPRESSED_CUMULATIVE_WDE_OVER_STREAM_WDESTRATEGY_H
