#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class UnionFindStruct
{
	array<int>^ p;
	Random^  rand;
public:

	UnionFindStruct(int max_X)
	{
		p = gcnew array<int>(max_X+1);
		rand = gcnew Random();
	}

	void MakeSet(int x)
	{
		p[x] = x;
	}

	int Find(int x)
	{
		if (p[x] == x) 
			return x;
		return p[x] = Find(p[x]);
	}

	void Unite(int x, int y)
	{
		
		x = Find(x);
		y = Find(y);
		//if (rand->Next() % 2 == 0)
		//	p[y] = x;
		p[x] = y;
	}
};

