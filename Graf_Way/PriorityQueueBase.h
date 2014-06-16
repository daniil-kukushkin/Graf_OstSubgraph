#pragma once
#include "Edge.h"

ref class PriorityQueueBase
{
public:

	PriorityQueueBase(void)
	{
	}

	virtual void Insert(int key, void* obj) = 0;
	virtual void* GetNext(int& minKey) = 0;
	virtual bool isEmpty() = 0;
};

