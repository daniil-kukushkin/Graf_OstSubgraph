#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
#include "PriorityQueueBase.h"
#include "Edge.h"

ref class HashTable : PriorityQueueBase
{
	array<List<KeyValue^>^>^ listArr;
	int maxKey;
	int arrSize;
	int kof;
	int count;
public:

	HashTable(int max_key)
	{
		count = 0;
		kof = 10;
		maxKey = max_key;
		arrSize = maxKey/kof;
		listArr = gcnew array<List<KeyValue^>^>(arrSize);
		for(int i=0; i<arrSize; i++)
			listArr[i] = gcnew List<KeyValue^>();
	}

	HashTable()
	{
		int max_key = 200;
		count = 0;
		kof = 10;
		maxKey = max_key;
		arrSize = maxKey/kof;
		listArr = gcnew array<List<KeyValue^>^>(arrSize);
		for(int i=0; i<arrSize; i++)
			listArr[i] = gcnew List<KeyValue^>();
	}

	virtual void Insert(int key, void* obj) override
	{
		int alias = (key < maxKey) ? key/kof : arrSize-1;
		KeyValue^ kv = gcnew KeyValue(key, obj);
		listArr[alias]->Add(kv);
		count++;
	}

	virtual void* GetNext(int& minKey) override
	{
		int k = 0;
		int nmin;
		void* res = nullptr;
		while(k < arrSize && listArr[k]->Count == 0)
			k++;

		if(k < arrSize)
		{
			minKey = 10e10, nmin = 0;
			for(int i=0; i<listArr[k]->Count; i++)
				if(listArr[k][i]->key < minKey)
				{
					nmin = i;
					minKey = listArr[k][i]->key;
				}
			res = listArr[k][nmin]->value;
			listArr[k]->RemoveAt(nmin);
			count--;
		}
		return res;
	}

	virtual bool isEmpty() override
	{
		return count == 0;
	}


};

