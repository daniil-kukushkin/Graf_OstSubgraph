#pragma once

ref class KeyValue{
public:
	int key;
	void* value;
	KeyValue(int key_, void* value_)
	{
		key = key_;
		value = value_;
	}
};

class Edge{
public:
	int v1, v2;
	Edge()
	{

	}
	Edge(int v1_, int v2_)
	{
		v1 = v1_;
		v2 = v2_;
	}
};

