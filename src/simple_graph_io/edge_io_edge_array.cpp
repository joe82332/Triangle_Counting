#include "edge_io.h"

// index[] points to the begin of dest[]
Edge_Array::Edge_Array(){
}
Edge_Array::Edge_Array( const Edge_List &b ){
	N = b.get_N() ;
	E = b.get_E() ;

	index = new uint32_t [N+1] ;	// [0] ~ [N]
	dest  = new uint32_t [E+1] ;	// +1 avoids empty allocation

	fill( b ) ;
}
Edge_Array::~Edge_Array(){
	if( index )
		delete [] index ;
	if( dest )
		delete [] dest ;
}


// fill data as host array
void Edge_Array::fill( const Edge_List &b ){
	if( E <= 0 )
		return ;

	index[0] = 0 ;
	uint32_t last_u = 0 ;

	// fill array
	for( size_t i=0 ; i<E ; i++ ){
		const uint32_t &u = b[i].first ;
		dest[i] = b[i].second ;

		// source (vector u) changed
		if( last_u != u ){
			for( last_u++ ; last_u < u ; last_u++ )
				index[last_u] = i ;
			index[u] = i ;
		}
	}

	// finalize
	for( last_u++ ; last_u <= N ; last_u++ )
		index[last_u] = E ;
}

size_t Edge_Array::get_N(void) const {
	return N ;
}
size_t Edge_Array::get_E(void) const {
	return E ;
}

const uint32_t* Edge_Array::get_index(void) const {
	return index ;
}
const uint32_t* Edge_Array::get_dest(void) const {
	return dest ;
}

