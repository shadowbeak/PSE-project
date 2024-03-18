//============================================================================
// Name        : DesignByContract.h
// Author      : Serge Demeyer, modified by Kasper Engelen
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : Declarations for design by contract in C++
//============================================================================

#include <assert.h>
#include <exception>

#ifdef __MINGW32__
#define REQUIRE(assertion, what) \
	if (!(assertion)) _assert (what, __FILE__, __LINE__)
#else
#define REQUIRE(assertion, what) \
	if (!(assertion)) __assert (what, __FILE__, __LINE__)
#endif


#ifdef __MINGW32__
#define ENSURE(assertion, what) \
	if (!(assertion)) _assert (what, __FILE__, __LINE__)
#else
#define ENSURE(assertion, what) \
	if (!(assertion)) __assert (what, __FILE__, __LINE__)
#endif


// Throws, instead of crashing
#define EXPECT(expected, what) \
	if (!(expected)) throw std::runtime_error(what)
