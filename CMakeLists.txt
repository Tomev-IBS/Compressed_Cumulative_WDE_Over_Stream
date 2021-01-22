cmake_minimum_required(VERSION 3.17)
project(Compressed_Cumulative_WDE_Over_Stream)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT d:/boost_1_75_0/)
FIND_PACKAGE(Boost)

IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

include_directories(include/Compressed_Cumulative_WDE_Over_Stream/)

add_executable(Compressed_Cumulative_WDE_Over_Stream include/Compressed_Cumulative_WDE_Over_Stream/CompressedCumulativeWaveletDensityEstimator.h src/CompressedCumulativeWaveletDensityEstimator.cpp include/Compressed_Cumulative_WDE_Over_Stream/TranslatedDilatedScalingFunction.h src/TranslatedDilatedScalingFunction.cpp include/Compressed_Cumulative_WDE_Over_Stream/WaveletDensityEstimator.h ../Compressed_Cumulative_WDE_Wrappers/LinearWDE.h ../Compressed_Cumulative_WDE_Wrappers/LinearWDE.cpp)

#if(NOT Boost_FOUND)
#    message(FATAL_ERROR "Could not find boost!")
#endif()
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")