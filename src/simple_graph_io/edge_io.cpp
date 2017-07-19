#include "edge_io.h"

#include <algorithm>

using namespace std ;


size_t Edge_List::get_N(void) const {
	return N ;
}

size_t Edge_List::get_E(void) const {
	return this->size() ;
}

void Edge_List::normalize(void){
	const size_t E = get_E() ;
	if( E == 0 )
		return ;

	// swap if necessary
	for( size_t i=0 ; i<E ; i++ ){
		pair<uint32_t,uint32_t> &edge = (*this)[i] ;

		if( edge.first < edge.second ){
			uint32_t t = edge.first ;
			edge.first = edge.second ;
			edge.second = t ;
		}
		else if( edge.first == edge.second )
			edge.first = edge.second = UINT32_MAX ;
	}

	// sort edge list
	std::sort( this->begin(), this->end() ) ;

	// insert first
	size_t i = 1 ;

	// fast pass if no redundancy
	for( ; i<E ; i++ ){
		if( (*this)[i] == (*this)[i-1] )
			break ;
	}

	// redundancy removal
	size_t inserted = i ;
	for( i++ ; i<this->size() ; i++ ){
		if( (*this)[i] != (*this)[inserted-1] &&
		    (*this)[i].first != UINT32_MAX )
			(*this)[inserted++] = (*this)[i] ;
	}

	// tailing unused edges (fix E)
	while( inserted > 0 ){
		if( (*this)[inserted-1].first < UINT32_MAX )
			break ;
		inserted -- ;
	}

	if( inserted != E )
		this->resize( inserted ) ;
}

void Edge_List::read_txt( istream &fin ){
	size_t E ;
	fin >> N >> E ;

	this->clear() ;
	this->reserve( E ) ;

	for( size_t i=0 ; i<E ; i++ ){
		uint32_t u=UINT32_MAX, v=UINT32_MAX ;
		fin >> u >> v ;
		this->push_back( make_pair(u,v) ) ;
	}
	normalize() ;
}

void Edge_List::write_txt( ostream &fout ) const {
	const size_t E = get_E() ;
	fout << N << ' ' << E << endl ;

	for( size_t i=0 ; i<E ; i++ )
		fout << (*this)[i].first << ' ' << (*this)[i].second << endl ;

	fout << flush ;
}

void Edge_List::read_bin( istream &fin ){
	size_t E ;
	fin.read( (char*)&N, sizeof(N) ) ;
	fin.read( (char*)&E, sizeof(E) ) ;

	this->resize( E ) ;
	fin.read( (char*)&(*this)[0], E*sizeof((*this)[0]) ) ;
	normalize() ;
}

void Edge_List::write_bin( ostream &fout ) const {
	const size_t E = get_E() ;
	fout.write( (char*)&N, sizeof(N) ) ;
	fout.write( (char*)&E, sizeof(E) ) ;

	fout.write( (char*)&(*this)[0], E*sizeof((*this)[0]) ) ;
}

