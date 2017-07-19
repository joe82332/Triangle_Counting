#ifndef __CUGL_SIMPLE_EDGE_IO_CUDA_H__
#define __CUGL_SIMPLE_EDGE_IO_CUDA_H__

#include "../simple_graph_io/edge_io.h"


class Edge_Array_Device : public Edge_Array {
public:
	Edge_Array_Device( const Edge_List &b ) ;
	~Edge_Array_Device() ;
} ;


class Edge_Array_Managed : public Edge_Array {
public:
	Edge_Array_Managed( const Edge_List &b ) ;
	~Edge_Array_Managed() ;
} ;


#endif

