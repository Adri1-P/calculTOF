include(CMakePrintHelpers)
cmake_minimum_required(VERSION 3.16)

project(Analyse)
# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
#list(APPEND /volatile3/root_v6.24.06.source/bin/bin $ENV{ROOTSYS})
list(APPEND /volatile3/root_v6.22.00.Linux-ubuntu20-x86_64-gcc9.3/root/bin/root $ENV{ROOTSYS})



#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
#cmake_print_variables(ROOTSYS)

#include(/biomaps/local/URANIE-4.5.0/include/*.h)
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


add_executable(analyse main.cc ${sources} ${headers})
target_link_libraries(analyse ${ROOT_LIBRARIES})


add_custom_target(Analyse DEPENDS analyse)


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS analyse DESTINATION bin)
