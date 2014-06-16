#pragma once
#include "Tree.h"
#include "PriorityQueueBase.h"

ref class QueueTree : public PriorityQueueBase
{
	Tree_* tree;
public:

	QueueTree(void)
	{
		tree = new Tree_();
	}
	
	virtual void Insert(int key, void* obj) override
	{
		Edge* e = (Edge*)obj;
		tree->insert(e, key);
	}

	virtual bool isEmpty() override
	{
		return tree->count == 0;
	}

	virtual void* GetNext(int& minKey) override
	{
		Node* node = tree->minimum();
		minKey = node->key;
		tree->deleteNode(node);
		return (void*)(node->data);
	}
	
};

