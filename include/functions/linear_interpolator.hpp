#ifndef __FUNCTIONS__LINEAR__INTERPOLATOR__HPP
#define __FUNCTIONS__LINEAR__INTERPOLATOR__HPP

#include <map>
#include "functions.h"
#include <string>
#include <exception>
#include <stdexcept>
#include <cmath>

namespace functions {

class LinearInterpolator:public std::map<double, double> {
public:
  //! @brief Gets the map from a file with a 2XN matrix
  LinearInterpolator(const std::string filename);
  //! @brief Gets the data
  LinearInterpolator(const std::string filename_x, const std::string filename_y);
  
  double interpolate(double x);
  bool inRange(double x);
};

} // Namespace functions

#endif
