#include "stdafx.h"
#include "UNDOREDO.h"
#include "stackM.h"

template <class T>
UNDOREDO<T>:: UNDOREDO(){};

template <class T>
UNDOREDO<T>:: UNDOREDO(const UNDOREDO &UR)
{
	UNDO=UR.UNDO;
	REDO=UR.REDO;
}

template <class T>
UNDOREDO<T>::~UNDOREDO() {};

template <class T>
void UNDOREDO<T>::AddNew (T nEle)
{
	UNDO.Push(nEle);
}
template <class T>
void UNDOREDO<T>::Delete()
{
	REDO.Push(UNDO.Pop());
}

template <class T>
void UNDOREDO<T>::Top()
{
	UNDO.Push(REDO.Pop());
}

template <class T>
void UNDOREDO<T>::PrintAll()
{
	StackM<T> RNEW;
	T El;
	cout<<"REDO:"<<endl;
	while(!REDO.Empty())
	{
		El=REDO.Pop();
		cout<<El<<endl;
		RNEW.Push(El);
	}
	while(!RNEW.Empty())
	{
		El=RNEW.Pop();
		REDO.Push(El);
	}
}
template <class T>
bool UNDOREDO<T>::isEmpty()
{
	return (REDO.Empty());
}

template <class T>
void UNDOREDO<T>::DeleteAll()
{
	while(!REDO.Empty())
		REDO.Pop();
	while(!UNDO.Empty())
		UNDO.Pop();
}