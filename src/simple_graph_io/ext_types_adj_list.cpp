#include "ext_graph_types.h"

#include <algorithm>

using namespace std ;


Adj_List::Adj_List(){
	E = 0 ;
}
Adj_List::Adj_List( const Edge_List &b ){
	*this = b ;
}

size_t Adj_List::get_N(void) const {
	return this->size() ;
}

size_t Adj_List::get_E(void) const {
	return E ;
}

void Adj_List::operator = ( const Edge_List &b ){
	this->clear() ;

	const size_t &N = b.get_N() ;
	this->resize( N ) ;

	E = b.get_E() ;
	// get degree
	vector <uint32_t> degree( N, 0 ) ;
	for( size_t i=0 ; i<E ; i++ ){
		const uint32_t &u = b[i].first ;
		const uint32_t &v = b[i].second ;
		degree[u] ++ ;
		degree[v] ++ ;
	}
	for( size_t i=0 ; i<N ; i++ )
		(*this)[i].reserve( degree[i] ) ;

	// fill list
	for( size_t i=0 ; i<E ; i++ ){
		const uint32_t &u = b[i].first ;
		const uint32_t &v = b[i].second ;

		(*this)[u].push_back( v ) ;
		(*this)[v].push_back( u ) ;
	}
}

