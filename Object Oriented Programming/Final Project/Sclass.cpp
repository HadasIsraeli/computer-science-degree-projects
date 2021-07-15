#include "stdafx.h"
#include "stackM.h"

template <class T, int nEl>
void StackM <T, nEl> :: Push (T elem)
	{
		data [nElements] = elem;
		nElements ++;
	}

template <class T, int nEl>
T StackM <T, nEl> :: Pop ()
	{
		nElements --;
		return data [nElements];
	}

template <class T, int nEl>
int StackM <T, nEl> :: Number ()
	{
		return nElements;
	}

template <class T, int nEl>
int StackM <T, nEl> :: Empty ()
	{
		return (nElements == 0);
	}

template <class T, int nEl>
int StackM <T, nEl> :: Full ()
	{
		return (nElements == nEl);
	}