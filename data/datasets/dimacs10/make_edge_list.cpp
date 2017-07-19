#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std ;


int main(void){
	string line ;

	size_t N, E ;
	getline( cin, line ) ;
	stringstream ssline( line ) ;
	ssline >> N >> E ;
	cout << N << " " << E << endl ;

	int progress = 0 ;
	for( size_t u=0 ; u<N ; u++ ){
		getline( cin, line ) ;
		stringstream ssline( line ) ;

		size_t v ;
		while( ssline >> v ){
			if( v-1 < u )
				cout << u << " " << v-1 << endl ;
			else
				break ;
		}

		if( 100.0*u/N >= progress ){
			cerr << progress << "%" << endl << flush ;
			progress += 10 ;
		}
	}
	cerr << progress << "%" << endl << flush ;

	cout << flush ;
	return 0 ;
}

