cmake_minimum_required(VERSION 2.8.3)
project(functions)

set (CMAKE_CXX_FLAGS -std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin)

catkin_package(
 INCLUDE_DIRS include include/functions
 LIBRARIES functions
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(include/functions include)

add_library(functions
  src/ArgumentData.cpp  src/DegMinSec.cpp  src/FormattedTime.cpp  src/functions.cpp
		src/HessianPlane.cpp src/linear_interpolator.cpp  src/Point3D.cpp  src/RandomNumberGenerator.cpp  src/RealVector.cpp
)
add_executable(test_interpolator src/test/test_interpolator.cpp)
target_link_libraries(test_interpolator functions)
add_executable(test_profiler src/test/test_profiler.cpp)
target_link_libraries(test_profiler functions)


## Mark executables and/or libraries for installation
install(TARGETS functions
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)

