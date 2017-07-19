#include "cugl/simple_graph_io_cuda/edge_io_cuda.h"

#include <iostream>

using namespace std ;


int main(void){
	Edge_List edge ;
	edge.read_txt( cin ) ;
	edge.write_txt( cout ) ;

	Edge_Array_Managed *graph = new Edge_Array_Managed( edge ) ;

	size_t N = graph->get_N() ;
	size_t E = graph->get_E() ;

	const uint32_t *index = graph->get_index() ;
	const uint32_t *dest = graph->get_dest() ;

	// index
	cout << "index:" << endl ;
	for( size_t i=0 ; i<=N ; i++ )
		cout << " " << i ;
	cout << endl ;

	for( size_t i=0 ; i<=N ; i++ )
		cout << " " << index[i] ;
	cout << endl ;

	// dest
	cout << "dest:" << endl ;
	for( size_t i=0 ; i<E ; i++ )
		cout << " " << i ;
	cout << endl ;

	for( size_t i=0 ; i<E ; i++ )
		cout << " " << dest[i] ;
	cout << endl ;

	delete graph ;
	return 0 ;
}

