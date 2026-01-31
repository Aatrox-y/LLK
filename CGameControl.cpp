#include "pch.h"
#include "CGameControl.h"
#include"CGameLogic.h"

bool CGameControl::Link(Vertex avPath[MRow * MCol], int& nVexnum)
{
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	int	info1 = m_graph.GetVertex(m_ptSelFirst.row * MCol + m_ptSelFirst.col);
	int	info2 = m_graph.GetVertex(m_ptSelSec.row * MCol + m_ptSelSec.col);

	if (info1 != info2 || info1 == BLANK || info2 == BLANK) return false;
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
		nVexnum = gameLogic.GetVexPath(avPath);

		return true;
	}

	return false;
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;

}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;

}

void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);

}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MCol + nCol);
}

bool CGameControl::IsWin(int nTime)
{
	CGameLogic logic;
	if (nTime <= 0)
	{
		m_graph.ClearGraph();
		return game_lose;
	}
	if (logic.IsBlank(m_graph) == true) {
		m_graph.ClearGraph(); 
		return game_win;
	}
	return game_play;
}

bool CGameControl::Help(Vertex avPath[MRow * MCol], int& nVexnum)
{
	CGameLogic gamelogic;

	if (gamelogic.IsBlank(m_graph) == true)
	{
		return false;
	}
	if (gamelogic.SearchValidPath(m_graph))
	{
		nVexnum = gamelogic.GetVexPath(avPath);

		return true;
	}
	return false;

}

void CGameControl::Reset()
{
	CGameLogic gamelogic;
	gamelogic.ResetGraph(m_graph);
}