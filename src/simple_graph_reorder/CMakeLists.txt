cmake_minimum_required(VERSION 2.8)

add_library( cugl_simple_graph_reorder reorder.cpp )

add_executable( reorder main_reorder.cpp )
target_link_libraries( 	reorder
			cugl_simple_graph_reorder
			cugl_simple_graph_io
			cugl_simple_graph_ext_types
			cugl_utility_timer )

#add_subdirectory()

#add_library()

#add_executable()
#target_link_libraries()

#cuda_add_library()
#cuda_add_executable()
