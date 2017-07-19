#ifndef __CUGL_SIMPLE_GRAPH_EXT_TYPES_H__
#define __CUGL_SIMPLE_GRAPH_EXT_TYPES_H__

#include "edge_io.h"

#include <cstdint>
#include <iostream>
#include <vector>

// Adj_List contains all edges needed
/* FORMAT of Adj_List:
N E
E0 v00 v01 v02
E1 v10 v11 v12
E2 v20 v21 v22
...
*/
class Adj_List : public std::vector< std::vector<uint32_t> > {
private:
	size_t E ;

public:
	Adj_List() ;
	Adj_List( const Edge_List &b ) ;

	size_t get_N(void) const ;
	size_t get_E(void) const ;

	void operator = ( const Edge_List &b ) ;
} ;


#endif

