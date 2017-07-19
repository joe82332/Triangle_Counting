#include "reorder.h"

#include "../simple_graph_io/ext_graph_types.h"

#include <vector>
#include <utility>
#include <algorithm>

using namespace std ;


static inline void relable( Edge_List &edge, const uint32_t *new_id ){
	const size_t &E = edge.get_E() ;
	for( size_t i=0 ; i<E ; i++ ){
		edge[i].first = new_id[edge[i].first] ;
		edge[i].second = new_id[edge[i].second] ;
	}
	edge.normalize() ;
}

void reorder_degree( Edge_List &edge ){
	const size_t &N = edge.get_N() ;
	const size_t &E = edge.get_E() ;

	vector <uint32_t> degree( N ) ;

	for( size_t i=0 ; i<E ; i++ ){
		degree[edge[i].first] ++ ;
		degree[edge[i].second] ++ ;
	}

	// <degree,V_id>
	vector < pair<uint32_t,uint32_t> > sort_buf ;
	sort_buf.reserve( N ) ;
	for( size_t i=0 ; i<N ; i++ )
		sort_buf.push_back( make_pair(UINT32_MAX-degree[i],i) ) ;

	// sort by degree (Reversed Order)
	sort( sort_buf.begin(), sort_buf.end() ) ;

	// New ID Mapping (Variable Renaming)
	vector <uint32_t> &new_id = degree ;
	for( size_t i=0 ; i<N ; i++ )
		new_id[sort_buf[i].second] = i ;

	// Relabel
	relable( edge, &new_id[0] ) ;
}

void reorder_degeneracy( Edge_List &edge ){
	const size_t &N = edge.get_N() ;

	Adj_List neighbor( edge ) ;

	// make rank_buf
	const size_t PAGE_ALIGN_MASK = 4096/sizeof(uint32_t)-1 ;
	const size_t bias = (N+PAGE_ALIGN_MASK)&(~PAGE_ALIGN_MASK) ;
	uint32_t *array = new uint32_t[bias*6] ;

	uint32_t *rank_buf = array ;	// uint32_t rank_buf[N]
	uint32_t *begin_in_rank = array + bias ;	// uint32_t begin_in_rank[N]
	uint32_t *end_in_rank = array + bias*2 ;	// uint32_t end_in_rank[N]

	uint32_t *degree = array + bias*3 ;	// uint32_t degree[N]
	uint32_t *id_in_rank = array + bias*4 ;	// uint32_t id_in_rank[N]

	uint32_t *new_id = array + bias*5;	// uint32_t new_id[N]

	fill_n( end_in_rank, N, 0 ) ;
	for( size_t v=0 ; v<N ; v++ ){
		const uint32_t &d = degree[v] = neighbor[v].size() ;
		end_in_rank[d] ++ ;
	}
	for( size_t d=1 ; d<N ; d++ )
		end_in_rank[d] += end_in_rank[d-1] ;

	copy_n( end_in_rank, N, begin_in_rank ) ;
	for( size_t v=N ; v-- ; ){
		id_in_rank[v] = --begin_in_rank[degree[v]] ;
		rank_buf[id_in_rank[v]] = v ;
	}

	// Degeneracy Ordering
	size_t min_degree = 0 ;
	for( uint32_t assigned = N ; assigned-- > 0 ; ){
		// find min_degree
		if( min_degree > 0 && end_in_rank[min_degree-1]-begin_in_rank[min_degree-1] )
			min_degree -- ;
		else{
			while( end_in_rank[min_degree]-begin_in_rank[min_degree] == 0 )
				min_degree ++ ;
		}

		// pop_back from min_degree
		uint32_t u = rank_buf[--end_in_rank[min_degree]] ;
		new_id[u] = assigned ;
		degree[u] = UINT32_MAX ;

		// update neighbors
		for( size_t i=0 ; i<neighbor[u].size() ; i++ ){
			const uint32_t &v = neighbor[u][i] ;

			if( degree[v] < UINT32_MAX ){
				// pop_front for degree[v]
				uint32_t front = rank_buf[begin_in_rank[degree[v]]++] ;
				id_in_rank[front] = id_in_rank[v] ;
				rank_buf[id_in_rank[front]] = front ;

				// push_back to degree[d-1]
				id_in_rank[v] = end_in_rank[--degree[v]]++ ;
				rank_buf[id_in_rank[v]] = v ;
			}
		}
	}

	// Relabel
	relable( edge, new_id ) ;

	delete [] array ;
}


