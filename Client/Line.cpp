#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine() : m_eLT(LT_NONE), m_eLS(LS_NONE)
{
}

CLine::CLine(LINE tLine)
	: m_tInfo(tLine)
{
}

CLine::CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint, LINE_TYPE eLT, LINE_SHAPE eLS)
	: m_tInfo(tLPoint, tRPoint), m_eLT(eLT), m_eLS(eLS)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	MoveToEx(hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY + iScrollY);

	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}
