#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CMonster::CMonster()
{
	ZeroMemory(&m_tStartInfo, sizeof(INFO));
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_fSpeed = 1.f;
	m_fMaxHp = 1.f;
	m_fCurHp = m_fMaxHp;
	m_eRender = GAMEOBJECT;
	m_tStartInfo = m_tInfo;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Dummy_Monster.bmp", L"Dummy_Monster");

}

int CMonster::Update()
{
	if (!g_bPause)
	{
		if (m_bDead)
			return OBJ_DEAD;

		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= m_fSpeed;
			break;
		case DIR_UP:
			m_tInfo.fY += m_fSpeed;
			break;
		case DIR_NONE:
			m_eCurState = MS_IDLE;
			break;
		case DIR_END:
			break;
		default:
			break;
		}

		Motion_Change();

		__super::Update_Rect();
	}
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (!g_bPause)
	{
		if (DIR_LEFT == m_eDir)
		{
			if (m_tInfo.fX <= m_tStartInfo.fX - m_fDirRad || m_tInfo.fX >= m_tStartInfo.fX + m_fDirRad)
			{
				m_fSpeed *= -1.f;
				if (m_fSpeed > 0)
				{
					m_eCurState = MS_LEFT_WALK;
				}
				if (m_fSpeed < 0)
				{
					m_eCurState = MS_RIGHT_WALK;
				}
			}
		}
		else if (DIR_UP == m_eDir)
		{
			if (m_tInfo.fY <= m_tStartInfo.fY - m_fDirRad || m_tInfo.fY >= m_tStartInfo.fY + m_fDirRad)
			{
				m_fSpeed *= -1.f;
			}
		}
		__super::Move_Frame();
	}
}

void CMonster::Render(HDC hDC)
{
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left, m_tRect.top + iScrollY, m_tRect.right, m_tRect.bottom + iScrollY);

	HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Dummy_Monster");
	GdiTransparentBlt(hDC,         // 복사 받을(최종적으로 그림을 그릴) DC를 전달
		m_tRect.left, // 복사 받을 위치의 좌표를 전달 (x,y 좌표)
		m_tRect.top + (long)iScrollY,
		(int)m_tInfo.fCX,   // 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,         // 비트맵을 가지고 있는 DC 전달
		m_tFrame.iFrameNow * 30,
		m_tFrame.iMotion * 35,
		30,   // 복사할 비트맵의 가로, 세로 사이즈
		35,
		RGB(255, 0, 232));

	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left, m_tRect.top + (long)iScrollY, m_tRect.right, m_tRect.bottom + (long)iScrollY);

	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

}


void CMonster::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case MS_IDLE:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameNow = 0;
            m_tFrame.iFrameEnd = 5;
            m_tFrame.iMotion = 2;
            m_tFrame.dwSpeed = 600;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MS_LEFT_WALK:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameNow = 0;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 150;
            m_tFrame.dwTime = GetTickCount64();
            break;

		case MS_RIGHT_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameNow = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount64();
			break;

        case MS_DEAD:
            m_tFrame.iFrameStart = 7;
            m_tFrame.iFrameNow = 7;
            m_tFrame.iFrameEnd = 7;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }

        m_ePreState = m_eCurState;
    }
}


void CMonster::Release()
{
}
