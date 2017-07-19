#ifndef __CUGL_SIMPLE_GRAPH_EDGE_IO_H__
#define __CUGL_SIMPLE_GRAPH_EDGE_IO_H__

#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

// An Edge_List stores edges (vertices pairs) in the LOWER triangular part
/* FORMAT of Edge_List:
N E
u0 v0
u1 v1
...
*/
class Edge_List : public std::vector< std::pair<uint32_t,uint32_t> > {
private:
	size_t N ;

public:
	size_t get_N(void) const ;
	size_t get_E(void) const ;
	void normalize(void) ;

	void read_txt( std::istream &fin ) ;
	void write_txt( std::ostream &fout ) const ;

	void read_bin( std::istream &fin ) ;
	void write_bin( std::ostream &fout ) const ;
} ;


class Edge_Array {
protected:
	// |N| & |E|
	size_t N, E ;

	// begin index & destination
	uint32_t *index, *dest ;

	// fill data as host array
	void fill( const Edge_List &b ) ;

	Edge_Array() ;

public:
	Edge_Array( const Edge_List &b ) ;
	~Edge_Array() ;

	size_t get_N(void) const ;
	size_t get_E(void) const ;

	const uint32_t *get_index(void) const ;
	const uint32_t *get_dest(void) const ;
} ;


#endif

