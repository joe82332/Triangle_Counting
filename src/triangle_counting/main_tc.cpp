#include "tc.h"
#include "../utility/timer.h"

#include <iostream>

using namespace std ;


int main(void){
	Timer global_timer ;

	global_timer.log( cerr, "Start Input..." ) ;
	Edge_List edge_list ;
	edge_list.read_txt( cin ) ;

	global_timer.log( cerr, "Making Edge Array..." ) ;
	Edge_Array edge_array( edge_list ) ;

	global_timer.log( cerr, "Counting Triangles..." ) ;
	uint64_t ans = triangle_counting( edge_array ) ;

	global_timer.log( cerr, "Done\n" ) ;

	cout << ans << "\ttriangles" << endl ;

	return 0 ;
}

