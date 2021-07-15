#pragma once
#include "stdafx.h"

template <class T, int nEl=1000> class StackM
{
public:
	T	data [nEl];
	int	nElements;
	StackM () :
		nElements (0)
		{ }

	// Adds an element to the stack

		
   const StackM operator=(const StackM &s)  
{
	data =s.data;
	nElements=s.nElements;
}


	void	Push (T elem);

	// Gets an element from the stack

	T	Pop ();

	// Number of elements actually on the stack

	int	Number ();

	// Is the stack empty?

	int	Empty ();

	// Is the stack full?

	int	Full ();
} ;