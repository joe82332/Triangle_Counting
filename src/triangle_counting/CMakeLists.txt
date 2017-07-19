cmake_minimum_required(VERSION 2.8)

add_library( cugl_triangle_counting tc.cpp )
cuda_add_library( cugl_triangle_counting_cuda tc_cuda_naive.cu tc_cuda_dual.cu )

add_executable( tc_cpu main_tc.cpp )
target_link_libraries( 	tc_cpu
			cugl_triangle_counting
			cugl_simple_graph_io
			cugl_utility_timer )

cuda_add_executable( tc_cuda main_tc_cuda.cpp )
target_link_libraries( 	tc_cuda
			cugl_triangle_counting_cuda
			cugl_simple_graph_io
			cugl_simple_graph_io_cuda
			cugl_utility_timer )

#add_subdirectory()

#add_library()

#add_executable()
#target_link_libraries()

#cuda_add_library()
#cuda_add_executable()
