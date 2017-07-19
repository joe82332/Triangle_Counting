#include "cugl/simple_graph_io/edge_io.h"

#include <iostream>

using namespace std ;


int main(void){
	Edge_List edge ;
	edge.read_txt( cin ) ;

	edge.write_bin( cout ) ;

	return 0 ;
}

