#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINE tLine);
	CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint, LINE_TYPE eLT, LINE_SHAPE eLS);
	~CLine();

public:
	LINE_TYPE Get_LineType() { return m_eLT; }
	LINE_SHAPE Get_LineShape() { return m_eLS; }

public:
	void         Render(HDC hDC);

public:
	const LINE& Get_Info() { return m_tInfo; }

private:
	LINE      m_tInfo;
	LINE_TYPE   m_eLT;
	LINE_SHAPE  m_eLS;
};