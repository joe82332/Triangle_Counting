#include "tc.h"


uint64_t triangle_counting( const Edge_Array &edge ){
	const uint32_t N = (uint32_t)edge.get_N() ;
	const uint32_t *index = edge.get_index() ;
	const uint32_t *dest = edge.get_dest() ;

	uint64_t sum = 0 ;

	// iterator: edge (u,v)
	for( uint32_t u=0 ; u<N ; u++ ){
		const uint32_t end_u = index[u+1] ;
		for( uint32_t i=index[u] ; i<end_u ; i++ ){
			const uint32_t v = dest[i] ;

			// set index
			uint32_t end_v = index[v+1] ;
			uint32_t iu = index[u] ;
			uint32_t iv = index[v] ;

			if( iv >= end_v )
				continue ;

			// fetch dest
			uint32_t du = dest[iu] ;
			uint32_t dv = dest[iv] ;

			for(;;){
				// update dest[] of u
				if( du <= dv ){
					// equal
					if( du == dv )
						sum ++ ;

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
	}

	return sum ;
}

