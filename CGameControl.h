#pragma once
#include"global.h"
#include"CGraph.h"
class CGameControl
{
private:
	CGraph m_graph;				
	Vertex m_ptSelFirst;	
	Vertex m_ptSelSec;		

public:
	void StartGame(void);								
	int GetElement(int nRow, int nCol);					
	bool Link(Vertex avPath[MRow * MCol], int& nVexnum); 
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool IsWin(int nTime);
	bool Help(Vertex avPath[MRow * MCol], int& nVexnum);
	void Reset();
};
