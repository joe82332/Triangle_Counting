#include "reorder.h"
#include "../simple_graph_io/ext_graph_types.h"
#include "../utility/timer.h"

#include <iostream>
#include <cstring>

using namespace std ;


void usage(){
	cerr << "Usage:" << endl ;
	cerr << "\treorder <-degree|-degeneracy> [-txt_in|-bin_in] [-txt_out|-bin_out]" << endl << endl ;

	cerr << "Options:" << endl ;
	cerr << "\t-degree:     Reorder by degree." << endl ;
	cerr << "\t-degeneracy: Apply degeneracy reordering." << endl ;
	cerr << "\t-txt_in:     (Default) Input by txt file." << endl ;
	cerr << "\t-bin_in:     Input by binary file." << endl ;
	cerr << "\t-txt_out:    (Default) Output in txt format." << endl ;
	cerr << "\t-bin_out:    Output in binary format." << endl ;
	cerr << flush ;
}

int main( int argc, char **argv ){
	if( argc < 2 ){
		usage() ;
		return 0 ;
	}

	Timer global_timer ;

	bool bin_in = false ;
	bool bin_out = false ;

	for( int i=2 ; i<argc ; i++ ){
		if( !strcmp("-bin_in", argv[i]) )
			bin_in = true ;

		else if( !strcmp("-bin_out", argv[i]) )
			bin_out = true ;
	}

	global_timer.log( cerr, "Start Input..." ) ;

	// Input
	Edge_List edge ;

	if( bin_in )
		edge.read_bin( cin ) ;
	else
		edge.read_txt( cin ) ;

	global_timer.log( cerr, "Start Reorder...") ;

	// Reorder
	if( !strcmp("-degree", argv[1]) )
		reorder_degree( edge ) ;
	else if( !strcmp("-degeneracy", argv[1]) )
		reorder_degeneracy( edge ) ;
	else{
		cerr << "No Reorder Method Specified!" << endl << flush ;
		cerr << "Output will be the (simplified) Original Graph." << endl << flush ;
	}

	global_timer.log( cerr, "Start Output...") ;

	// Output
	if( bin_out )
		edge.write_bin( cout ) ;
	else
		edge.write_txt( cout ) ;

	global_timer.log( cerr, "Done") ;
	cerr << endl << flush ;

	return 0 ;
}

