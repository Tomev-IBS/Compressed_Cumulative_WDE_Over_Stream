#include <boost/math/special_functions/daubechies_scaling.hpp>
#include <boost/math/special_functions/daubechies_wavelet.hpp>
#include <boost/math/filters/daubechies.hpp>

#include <vector>
#include <iostream>

#include "CompressedCumulativeWaveletDensityEstimator.h"
#include "WDE_Strategies/LinearWDEStrategy.h"


using boost::math::daubechies_scaling;
using boost::math::daubechies_wavelet;
using boost::math::filters::daubechies_scaling_filter;
using std::vector;
using std::cout;
using std::endl;


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

void TestDaubechiesFilters(){
  constexpr const int p = 5;
  auto filter = daubechies_scaling_filter<double, p>();

  std::cout << "Filters: \n";
  for(auto h : filter){
    std::cout << h << std::endl;
  }
  std::cout << "End filters.\n\n";
}

vector<double> GenerateRandomVector(const unsigned int &n){
  vector<double> the_vector = {};

  for(int i = 0; i < n; ++i){
    //the_vector.push_back((double) rand() / RAND_MAX);
    the_vector.push_back((double) rand());
  }

  return the_vector;
}

void TestLinearWDEGetValue(){
  cout << "TestLinearWDEGetValue\n\nGenerating vector.\n";
  auto v = GenerateRandomVector(100);

  cout << "Generating strategy. \n";
  auto strategy = LinearWDEStrategy();

  cout << "Updating strategy. \n";
  strategy.UpdateWDEData(v);

  cout << "Evaluating strategy.\n";
  std::cout << strategy.GetValue(1) << endl;

  cout << "Done.\n";
}

void TestResolutionLoweringSize(){
  cout << "TestResolutionLoweringSize\n\nGenerating vector.\n";
  auto v = GenerateRandomVector(1000);

  cout << "Generating strategy. \n";
  auto strategy = LinearWDEStrategy();

  cout << "Updating strategy. \n";
  strategy.UpdateWDEData(v);

  cout << "Evaluating strategy.\n";
  std::cout << strategy.GetValue(1) << endl;

  cout << "Lowering resolution.\n";
  strategy.LowerResolution();

  cout << "Evaluating strategy.\n";
  std::cout << strategy.GetValue(1) << endl;

  cout << "Lowering resolution.\n";
  strategy.LowerResolution();

  cout << "Evaluating strategy.\n";
  std::cout << strategy.GetValue(1) << endl;

  cout << "Done.\n";
}

int main() {
  //TestDaubechies();
  //TestDaubechiesFilters();
  //TestLinearWDEGetValue();
  TestResolutionLoweringSize();


}



