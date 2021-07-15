
#ifndef UNDOREDO_H
#define UNDOREDO_H
#include "stdafx.h"
#include "stackM.h"



template <class T>class UNDOREDO
{
private:
	
public:
	StackM<T> UNDO;
	StackM<T> REDO;
	UNDOREDO();
	UNDOREDO(const UNDOREDO &);
	~UNDOREDO();
	void AddNew(T);
	void Delete();
	void Top();
	void PrintAll();
	bool isEmpty();
	void DeleteAll();

};
#endif