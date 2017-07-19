#ifndef __CUGL_TRIANGLE_COUNTING_H___
#define __CUGL_TRIANGLE_COUNTING_H___

#include "../simple_graph_io/edge_io.h"
#include "../simple_graph_io_cuda/edge_io_cuda.h"

uint64_t triangle_counting( const Edge_Array &edge ) ;

uint64_t triangle_counting_cuda_naive( const Edge_Array_Device &edge ) ;

uint64_t triangle_counting_cuda_dual( const Edge_Array_Device &edge ) ;

#endif

