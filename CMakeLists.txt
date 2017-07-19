cmake_minimum_required(VERSION 2.8)

SET(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_compile_options(-Wall -O3 -std=c++11)
#add_compile_options(-fopenmp)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")

find_package(CUDA)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS};-arch=sm_35")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS};-O3")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS};-std=c++11")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS};-Xcompiler -Wall,-O3")
#set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS};-Xcompiler -fopenmp")

#add_compile_options(-flto)
#SET(CMAKE_AR gcc-ar)
#SET(CMAKE_RANLIB gcc-ranlib)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")

add_subdirectory(src)

