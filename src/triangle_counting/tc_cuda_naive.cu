#include "tc.h"

__global__ void kernel_tc_naive(
		uint64_t* __restrict__ sum,
		const uint32_t* __restrict__ index,
		const uint32_t* __restrict__ dest,
		const uint32_t N ){

	const uint32_t u = blockIdx.x*blockDim.y + threadIdx.y ;
	if( u >= N )
		return ;

	const uint32_t start_u = index[u] ;
	const uint32_t end_u = index[u+1] ;

	uint32_t val = 0 ;
	for( uint32_t i=index[u]+threadIdx.x ; i<end_u ; i+=blockDim.x ){
		const uint32_t v = dest[i] ;

		// set index
		uint32_t end_v = index[v+1] ;
		uint32_t iv = index[v] ;
		if( iv >= end_v )
			continue ;

		uint32_t iu = start_u ;

		// fetch dest
		uint32_t du = dest[iu] ;
		uint32_t dv = dest[iv] ;

		for(;;){
			// update dest[] of u
			if( du <= dv ){
				// equal
				if( du == dv )
					val ++ ;

				if( ++iu >= end_u )
					break ;
				du = dest[iu] ;
			}

			// update dest[] of v
			else{
				if( ++iv >= end_v )
					break ;
				dv = dest[iv] ;
			}
		}
	}

	// reduce
	#pragma unroll
	for ( int offset = warpSize/2; offset > 0; offset /= 2 )
		val += __shfl_down( val, offset );
	if( threadIdx.x == 0 && val > 0 )
		atomicAdd( (unsigned long long*)sum, (unsigned long long)val ) ;
}

uint64_t triangle_counting_cuda_naive( const Edge_Array_Device &edge ){
	const uint32_t N = (uint32_t)edge.get_N() ;
	const uint32_t *index = edge.get_index() ;
	const uint32_t *dest = edge.get_dest() ;

	uint64_t *sum ;
	cudaMallocManaged( &sum, sizeof(uint64_t) ) ;
	*sum = 0 ;

	dim3 threads(32,32) ;
	dim3 blocks((N+threads.y-1)/threads.y) ;
	kernel_tc_naive <<< blocks, threads >>> ( sum, index, dest, N ) ;
	cudaDeviceSynchronize() ;

	uint64_t re = *sum ;
	cudaFree( sum ) ;

	return re ;
}

