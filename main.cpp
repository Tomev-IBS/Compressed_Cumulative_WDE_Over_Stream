#include <boost/math/special_functions/daubechies_scaling.hpp>
#include <boost/math/special_functions/daubechies_wavelet.hpp>

#include <vector>
#include <iostream>

#include "CompressedCumulativeWaveletDensityEstimator.h"

using boost::math::daubechies_scaling;
using boost::math::daubechies_wavelet;
using std::vector;
using std::cout;


void TestDaubechies(){
  constexpr const int p = 8;
  auto phi = daubechies_scaling<double, p>();
  std::cout << "phi(0.25) = " << phi(0.25) << "\n";
  std::cout << "phi'(0.25) = " << phi.prime(0.25) << "\n";
  std::cout << "phi''(0.25) = " << phi.double_prime(0.25) << "\n";
  auto [a, b] = phi.support();
  std::cout << "Support: [" << a << ", " << b << "]\n";
  // The wavelet:
  auto psi = daubechies_wavelet<double, p>();
  // ...
}

vector<double> GenerateRandomVector(const unsigned int &n){
  vector<double> the_vector = {};

  for(int i = 0; i < n; ++i){
    the_vector.push_back((double) rand() / RAND_MAX);
  }

  return the_vector;
}

int main() {
  //TestDaubechies();

  auto v = GenerateRandomVector(6);

  for(auto val : v){
    cout << val << std::endl;
  }

  auto est = CompressedCumulativeWaveletDensityEstimator();

  std::cout << "\nEst\n\n";

  est.UpdateEstimator(v);

}



