#include "timer.h"

#include <iomanip>

using namespace std ;


Timer::Timer(){
	reset() ;
}

void Timer::reset(){
	start = last = chrono::high_resolution_clock::now() ;
}

void Timer::log( ostream &fout, const char *message ){
	chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now() ;

	if( start < last ){
		fout << fixed << setprecision(3) << "  "
			<< chrono::duration_cast<chrono::microseconds>(now-last).count()/1000.0
			<< "  ms" << endl ;
	}
	last = now ;

	fout << fixed << setprecision(6) << "["
		<< chrono::duration_cast<chrono::microseconds>(now-start).count()/1000000.0
		<< "s] " << message << flush ;
}

double Timer::duration_s() const {
	return duration_us()/1000000.0 ;
}

double Timer::duration_ms() const {
	return duration_us()/1000.0 ;
}

double Timer::duration_us() const {
	return chrono::duration_cast<chrono::microseconds>
		(chrono::high_resolution_clock::now()-start).count() ;
}

