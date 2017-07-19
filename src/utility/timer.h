#ifndef __CUGL_TIMER_H__
#define __CUGL_TIMER_H__

#include <chrono>
#include <iostream>

class Timer{
private:
	std::chrono::high_resolution_clock::time_point start, last ;

public:
	Timer() ;
	void reset() ;

	void log( std::ostream &fout, const char *message ) ;
	double duration_s() const ;
	double duration_ms() const ;
	double duration_us() const ;
} ;

#endif

