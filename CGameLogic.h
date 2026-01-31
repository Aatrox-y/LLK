#pragma once
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
protected:
	Vertex m_avPath[MRow * MCol];
	void AddVertex(Vertex v);
	int m_nVexNum;
	void DeleteVertex();
	int m_nCorner;
	int m_anPath[MRow * MCol];


public:
	CGameLogic();
	~CGameLogic();

	void InitMap(CGraph& graph);
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);
	void Clear(CGraph& graph, Vertex v1, Vertex v2);
	void UpdateArc(CGraph& graph, int nRow, int nCol);
	int GetVexPath(Vertex avPath[MRow * MCol]);
	void PushVertex(int nV);
	void PopVertex();
	bool SearchPath(CGraph& graph, int nV0, int nV1);
	bool IsExsit(int nVi);
	bool IsCornor();
	bool IsBlank(CGraph& graph);
	bool SearchValidPath(CGraph& graph);
	void ResetGraph(CGraph& graph);

};
