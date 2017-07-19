#include "edge_io_cuda.h"

// index[] points to the begin of dest[]
Edge_Array_Managed::Edge_Array_Managed( const Edge_List &b ){
	N = b.get_N() ;
	E = b.get_E() ;

	cudaMallocManaged( &index, (N+1)*sizeof(uint32_t) ) ;	// [0] ~ [N]
	cudaMallocManaged( &dest,  (E+1)*sizeof(uint32_t) ) ;	// +1 avoids empty allocation

	fill( b ) ;
}
Edge_Array_Managed::~Edge_Array_Managed(){
	if( index ){
		cudaFree( index ) ;
		index = NULL ;
	}

	if( dest ){
		cudaFree( dest ) ;
		dest = NULL ;
	}
}


