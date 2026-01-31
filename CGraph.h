#pragma once
class CGraph
{
public:
	CGraph();
	~CGraph();
public:

#define MAX_VERTEX_NUM 160				
	typedef int Vertices[MAX_VERTEX_NUM];	
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int AddVertex(int info);
	int GetVertex(int nIndex);
	int GetVexnum();
	void AddArc(int nV1Index, int nV2Index);
	bool GetArc(int nV1Index, int nV2Index);
	void UpdateVertex(int nIndex, int info);
	void ClearGraph();
	void Change(int n1, int n2);
protected:

	AdjMatrix m_AdjMatrix;
	Vertices m_Vertices;
	int m_nVexnum;
	int m_nArcnum;
	void InitGraph();

};

