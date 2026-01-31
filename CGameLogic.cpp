#include "pch.h"
#include "CGameLogic.h"
#include"global.h"
#include<cstdlib>
#include<ctime>
#include"CGraph.h"
CGameLogic::CGameLogic()
{

	m_nVexNum = 0;  
	m_nCorner = 0;     
}

CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(CGraph& graph)
{
	srand((int)time(NULL));
	int anTemp[MRow][MCol];
	int a = 0;
	for (int j = 0; j < MCol; j++) {
		for (int i = 0; i < MRow; i++) {
			anTemp[i][j] = j;
		}
	}
	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {
			int i1 = rand() % MRow;
			int j1 = rand() % MCol;
			int t = anTemp[i][j];
			anTemp[i][j] = anTemp[i1][j1];
			anTemp[i1][j1] = t;
		}
	}
	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {
			graph.AddVertex(anTemp[i][j]);
		}
	}
	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {
			UpdateArc(graph, i, j);
		}
	}

}
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nV1Index = nRow * MCol + nCol;

	if (nCol > 0) {
		int nV2Index = nV1Index - 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nCol < MCol - 1) {
		int nV2Index = nV1Index + 1;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow > 0) {
		int nV2Index = nV1Index - MCol;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow < MRow - 1) {
		int nV2Index = nV1Index + MCol;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK)
		{
			graph.AddArc(nV1Index, nV2Index);
		}
	}
}
void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}
void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}
void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * MCol + v1.col;
	int nV2Index = v2.row * MCol + v2.col;
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}
int CGameLogic::GetVexPath(Vertex avPath[MRow * MCol])
{
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < MCol; point.col++)
		{
			for (point.row = 0; point.row < MRow; point.row++)
			{
				if (point.row * MCol + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}

	return m_nVexNum;
}
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * MCol + v1.col;
	int nV2Index = v2.row * MCol + v2.col;
	PushVertex(nV1Index);
	if (SearchPath(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}
	PopVertex();
	return false;
}
bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	int nVexnum = graph.GetVexnum();
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			PushVertex(nVi);
			if (m_nCorner > 2)
			{
				PopVertex();
				continue;
			}
			if (nVi != nV1)
			{
				if (graph.GetVertex(nVi) != BLANK)
				{
					PopVertex();
					continue;
				}
				if (SearchPath(graph, nVi, nV1))
				{
					return true;
				}
			}
			else
			{
				return true;
			}

			PopVertex();    
		}
	}
	return false;
}
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi) return true;
	}
	return false;
}
bool CGameLogic::IsCornor(void)
{
	if (m_nVexNum >= 3)
	{
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}
void CGameLogic::PushVertex(int nV)
{
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;
	if (IsCornor())
	{
		m_nCorner++;
	}
}
void CGameLogic::PopVertex()
{
	if (IsCornor())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}
bool CGameLogic::IsBlank(CGraph& graph)
{
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++) {
		if (graph.GetVertex(i) != BLANK) return false;
	}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph& graph)
{
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		if (graph.GetVertex(i) == BLANK)continue;
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				if (graph.GetVertex(i) == graph.GetVertex(j))
				{
					PushVertex(i);
					if (SearchPath(graph, i, j) == true)
					{
						return true;
					}
					PopVertex();
				}

			}
		}
	}
	return false;
}
void CGameLogic::ResetGraph(CGraph& graph)
{
	srand((int)time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int n1 = rand() % MAX_VERTEX_NUM;
		int n2 = rand() % MAX_VERTEX_NUM;
		graph.Change(n1, n2);
	}
	for (int i = 0; i < MRow; i++)
	{
		for (int j = 0; j < MCol; j++)
		{
			UpdateArc(graph, i, j);
		}
	}

}