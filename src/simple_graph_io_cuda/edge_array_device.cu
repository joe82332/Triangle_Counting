#include "edge_io_cuda.h"

// index[] points to the begin of dest[]
Edge_Array_Device::Edge_Array_Device( const Edge_List &b ) : Edge_Array(b) {
	uint32_t *_index = index ;
	uint32_t *_dest = dest ;

	cudaMalloc( &index, (N+1)*sizeof(uint32_t) ) ;	// [0] ~ [N]
	cudaMalloc( &dest,  (E+1)*sizeof(uint32_t) ) ;	// +1 avoids empty allocation

	cudaMemcpy( index, _index, (N+1)*sizeof(uint32_t), cudaMemcpyDefault ) ;
	cudaMemcpy( dest, _dest, (E+1)*sizeof(uint32_t), cudaMemcpyDefault ) ;

	delete [] _index ;
	delete [] _dest ;
}
Edge_Array_Device::~Edge_Array_Device(){
	if( index ){
		cudaFree( index ) ;
		index = NULL ;
	}

	if( dest ){
		cudaFree( dest ) ;
		dest = NULL ;
	}
}


