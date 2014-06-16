#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

#include "UnionFindStruct.h"
#include "Edge.h"
#include "QueueTree.h"
#include "QueueHeap.h"
#include "HashTable.h"

const int Radius = 10;

ref class Vertex{
	Pen^ pen;
public:
	int x,y;
	int Number;
	Vertex(void )
	{
		x = y = -1;
		Number = -1;
		pen = gcnew Pen(Color::Red);
	}
	Vertex(int xi, int yi, int Num): x(xi), y(yi), Number(Num)
	{
		pen = gcnew Pen(Color::Red);
	}
	void Draw(BufferedGraphics ^buff)
	{
		Font^ drawFont = gcnew Font( "Arial",12 );
		SolidBrush^ drawBrush = gcnew SolidBrush( Color::Green );

		buff->Graphics->DrawEllipse(pen, x-Radius, y-Radius, Radius*2, Radius*2);
		buff->Graphics->DrawString(Convert::ToString(Number), drawFont, drawBrush, x-Radius+3, y-Radius+1);
	}
};

ref class Graf
{
	int vertexCount, edgeCount;
	int** adjMatrix;
	int** ostGrMatrix;
	List<Vertex^>^ vertexList;
	int maxVertex;
public:

	Graf(int maxVertex)
	{
		vertexCount = maxVertex;
		edgeCount = 0;
		
		adjMatrix = new int*[vertexCount];
		for(int i=0; i<vertexCount; i++)
			adjMatrix[i] = new int[vertexCount];

		for(int i=0; i<vertexCount; i++)
			for(int j=0; j<vertexCount; j++)
				adjMatrix[i][j] = 0;
		
		ostGrMatrix = nullptr;

		ostGrMatrix = new int*[vertexCount];
		for(int i=0; i<vertexCount; i++)
			ostGrMatrix[i] = new int[vertexCount];

		vertexCount = 0;

		vertexList = gcnew List<Vertex^>();
	}

	void Add(int x, int y)
	{
		vertexList->Add( gcnew Vertex(x, y, vertexList->Count) ); // всегда добавляем вершину со следующим номером
	}

	bool AddEdge(int anum, int bnum, int weight)
	{
		if(anum < vertexList->Count && anum >= 0 && bnum < vertexList->Count && bnum >= 0)
		{
			adjMatrix[ anum ][ bnum ] = weight;
			adjMatrix[ bnum ][ anum ] = weight;
			edgeCount++;
		}
		else return false;
	}

	Vertex^ GetVertex(int x, int y)
	{
		for(int i=0; i<vertexList->Count; i++)
			if( Math::Sqrt( (double)Math::Abs(x-vertexList[i]->x)*Math::Abs(x-vertexList[i]->x) + Math::Abs(y-vertexList[i]->y)*Math::Abs(y-vertexList[i]->y) ) < Radius )
				return vertexList[i];
		return nullptr;
	}


	void findOstSubgraf(PriorityQueueBase^ q)
	{
		try
		{
			if(edgeCount == 0)
				return;
			vertexCount = vertexList->Count;
			for(int i=0; i<vertexCount-1; i++)
				for(int j=i+1; j<vertexCount; j++)
				{
					if(adjMatrix[i][j] > 0)
						q->Insert( adjMatrix[i][j], (void*)(new Edge(i,j)) );
				}
			UnionFindStruct^ Vs = gcnew UnionFindStruct(vertexCount);
			for(int i=0; i<vertexCount; i++)
				Vs->MakeSet(i);
			Edge* tempE;
			array<Edge*>^ ostSubgrafE = gcnew array<Edge*>(vertexCount-1);
			int ostEdgeCount = 0;
			int w;
			while(1)
			{
				if(!q->isEmpty())
				{
					tempE = (Edge*)(q->GetNext(w));
					if(Vs->Find(tempE->v1) == Vs->Find(tempE->v2))
						continue;
					Vs->Unite(tempE->v1, tempE->v2);
					ostSubgrafE[ostEdgeCount] = tempE;
					ostEdgeCount++;
				} else
					break;
			}

			for(int i=0; i<vertexCount; i++)
				for(int j=0; j<vertexCount; j++)
					ostGrMatrix[i][j] = 0;

			for(int i=0; i<vertexCount-1; i++)
			{
				if(ostSubgrafE[i]->v1 < ostSubgrafE[i]->v2)
					ostGrMatrix[ostSubgrafE[i]->v1][ostSubgrafE[i]->v2] = 1;
				else
					ostGrMatrix[ostSubgrafE[i]->v2][ostSubgrafE[i]->v1] = 1;
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show("С графом что-то не так." + Environment::NewLine + "Вероятно он не связный.");
		}
	}

	void Clear()
	{
		for(int i=0; i<vertexList->Count; i++)
			for (int j=0; j<vertexList->Count; j++)
				adjMatrix[i][j] = 0;
		vertexList->Clear();
	}

	void Draw(BufferedGraphics ^buff)
	{
		for(int i=0; i<vertexList->Count; i++)
			vertexList[i]->Draw(buff);

		Pen^ pen = gcnew Pen(Color::Black);
		for(int i=0; i<vertexList->Count; i++)
			for (int j=i+1; j<vertexList->Count; j++)
			{
				if( adjMatrix[i][j] > 0 || adjMatrix[j][i] > 0 )
				{
					if(ostGrMatrix[i][j] > 0)
						pen->Color = Color::Orange;
					else
						pen->Color = Color::Blue;

					buff->Graphics->DrawLine(pen, vertexList[i]->x, vertexList[i]->y, vertexList[j]->x, vertexList[j]->y);

					Font^ drawFont = gcnew Font( "Arial",12 );
					SolidBrush^ drawBrush = gcnew SolidBrush( Color::DarkViolet );
					buff->Graphics->DrawString( Convert::ToString(adjMatrix[i][j]), drawFont, drawBrush, 
						Math::Min(vertexList[i]->x,vertexList[j]->x) + Math::Abs(vertexList[i]->x-vertexList[j]->x)/2, 
						Math::Min(vertexList[i]->y,vertexList[j]->y) + Math::Abs(vertexList[i]->y-vertexList[j]->y)/2);
				}
			}
	}

};

