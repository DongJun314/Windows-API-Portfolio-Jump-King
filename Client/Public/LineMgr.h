#pragma once
#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	bool	Collision_Line(float* pY, float fX, float fY);
	bool	Collision_Wall(float* pY, float fX, float fY);

public:
	void	Initialize(void);
	void	Update(void);
	void	Render(HDC hDC);
	void	Release();

public:
	list<CLine*>* Get_LineList() { return &m_LineList; }

public:
	void	Save_Line(void);
	void	Load_Line(void);

private:
	list<CLine*>		 m_LineList;
	static CLineMgr*	 m_pInstance;
};

