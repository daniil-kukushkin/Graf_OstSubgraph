#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
#include "PriorityQueueBase.h"



ref class QueueHeap : public PriorityQueueBase
{
	List<KeyValue^>^ list1;
	
	int heapSize()
	{
		int c = list1->Count;
		return c;
	}
	
public:

	QueueHeap(void)
	{
		list1 = gcnew List<KeyValue^>();
	}

	virtual void Insert(int key, void* obj) override
	{
		KeyValue^ keyVal= gcnew KeyValue(-key, obj);
		list1->Add(keyVal);
		int i = heapSize() - 1;
		int parent = (i - 1) / 2;

		while (i > 0 && list1[parent]->key < list1[i]->key)
		{
			KeyValue^ temp = list1[i];
			list1[i] = list1[parent];
			list1[parent] = temp;

			i = parent;
			parent = (i - 1) / 2;
		}
	}

	virtual bool isEmpty() override
	{
		return heapSize() == 0;
	}

	void heapify(int i)
	{
		int leftChild;
		int rightChild;
		int largestChild;

		for (; ; )
		{
			leftChild = 2 * i + 1;
			rightChild = 2 * i + 2;
			largestChild = i;

			if (leftChild < heapSize() && list1[leftChild]->key > list1[largestChild]->key) 
			{
				largestChild = leftChild;
			}

			if (rightChild < heapSize() && list1[rightChild]->key > list1[largestChild]->key)
			{
				largestChild = rightChild;
			}

			if (largestChild == i) 
			{
				break;
			}

			KeyValue^ temp = list1[i];
			list1[i] = list1[largestChild];
			list1[largestChild] = temp;
			i = largestChild;
		}
	}

	virtual void* GetNext(int& minKey) override
	{
		KeyValue^ result = list1[0];
		list1[0] = list1[heapSize() - 1];
		list1->RemoveAt(heapSize() - 1);
		minKey = -result->key;
		heapify(0);
		return result->value;
	}

};

