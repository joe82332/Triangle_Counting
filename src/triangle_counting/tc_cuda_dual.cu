#include "tc.h"

__global__ void kernel_tc_dual(
		uint64_t* __restrict__ sum,
		const uint32_t* __restrict__ index,
		const uint32_t* __restrict__ dest,
		const uint32_t N ){

	const uint32_t u = blockIdx.x*blockDim.z + threadIdx.z ;
	if( u >= N )
		return ;

	const uint32_t end_u = index[u+1] ;

	uint32_t val = 0 ;
	for( uint32_t i=index[u]+threadIdx.x ; i<end_u ; i+=blockDim.x ){
		uint32_t v ;
		if( threadIdx.y == 0 )
			v = u ;
		else
			v = dest[i] ;

		// set index
		uint32_t iv = index[v] ;
		const uint32_t end_v = index[v+1] ;

		// fetch dest
		uint32_t dv ;

		int done = 0 ;
		if( iv >= end_v )
			done = 1 ;
		else
			dv = dest[iv] ;

		for(;;){
			done += __shfl_xor( done, 16 ) ;
			if( done )
				break ;

			uint32_t du = __shfl_xor( dv, 16 ) ;

			// update dest[] of v
			if( dv <= du ){
				// equal
				if( dv == du )
					val ++ ;

				if( ++iv >= end_v )
					done = 1 ;
				else
					dv = dest[iv] ;
			}
		}
	}

	// reduce
	#pragma unroll
	for ( int offset = blockDim.x/2; offset > 0; offset /= 2 )
		val += __shfl_down( val, offset );
	if( threadIdx.y + threadIdx.x == 0 && val > 0 )
		atomicAdd( (unsigned long long*)sum, (unsigned long long)val ) ;
}


uint64_t triangle_counting_cuda_dual( const Edge_Array_Device &edge ){
	const uint32_t N = (uint32_t)edge.get_N() ;
	const uint32_t *index = edge.get_index() ;
	const uint32_t *dest = edge.get_dest() ;

	uint64_t *sum ;
	cudaMallocManaged( &sum, sizeof(uint64_t) ) ;
	*sum = 0 ;

	dim3 threads(16,2,32) ;
	dim3 blocks((N+threads.z-1)/threads.z) ;
	kernel_tc_dual <<< blocks, threads >>> ( sum, index, dest, N ) ;
	cudaDeviceSynchronize() ;

	uint64_t re = *sum ;
	cudaFree( sum ) ;

	return re ;
}

