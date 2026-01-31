#include "pch.h"
#include "CGraph.h"

CGraph::CGraph()
{
	InitGraph();  
}


CGraph::~CGraph()
{
}
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}

}


int CGraph::AddVertex(int info)
{
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return 0;
	}
	m_Vertices[m_nVexnum] = info;
	m_nVexnum++;
	return m_nVexnum;
}
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

int CGraph::GetVexnum()
{
	return m_nVexnum;
}

void CGraph::ClearGraph(void)
{
	InitGraph();
}

void CGraph::Change(int n1, int n2) {
	int t = m_Vertices[n1];
	m_Vertices[n1] = m_Vertices[n2];
	m_Vertices[n2] = t;
}