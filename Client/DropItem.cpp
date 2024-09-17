#include "stdafx.h"
#include "DropItem.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CDropItem::CDropItem()
{
}

CDropItem::~CDropItem()
{
	Release();
}

void CDropItem::Initialize()
{
	m_eRender = BG;
    m_eCurState = DIS_IDLE;
    
    m_tFrame.iFrameStart = 1;
    m_tFrame.iFrameNow = 1;
    m_tFrame.iFrameEnd = 1;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 300;
    m_tFrame.dwTime = GetTickCount64();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Item.bmp", L"Item_Lightnening");
}

int CDropItem::Update()
{
    if (!g_bPause)
    {
        if (m_bDead)
        {
            if (m_dwTime + 1000 < GetTickCount64())
            {
                return OBJ_DEAD;
            }
            else if (m_dwTime + 300 < GetTickCount64())
            {

            }
            else 
            {
                m_tInfo.fY -= 2.f;
            }
        }

        Motion_Change();

        __super::Update_Rect();
    }
	return OBJ_NOEVENT;
}

void CDropItem::Late_Update()
{
    if (!g_bPause)
    {
        __super::Move_Frame();
    }
}

void CDropItem::Render(HDC hDC)
{
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Item_Lightnening");
    GdiTransparentBlt(hDC,         // 복사 받을(최종적으로 그림을 그릴) DC를 전달
        m_tRect.left, // 복사 받을 위치의 좌표를 전달 (x,y 좌표)
        m_tRect.top + (long)iScrollY,
        (int)m_tInfo.fCX,   // 복사 받을 가로, 세로 길이
        (int)m_tInfo.fCY,
        hMemDC,         // 비트맵을 가지고 있는 DC 전달
        m_tFrame.iFrameNow * 50,
        m_tFrame.iMotion * 50,
        50,   // 복사할 비트맵의 가로, 세로 사이즈
        50,
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

void CDropItem::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case DIS_IDLE:
            m_tFrame.iFrameStart = 1;
            m_tFrame.iFrameNow = 1;
            m_tFrame.iFrameEnd = 1;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 300;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }

        m_ePreState = m_eCurState;
    }
}

void CDropItem::Release()
{
}

void CDropItem::Collision(OBJ_ID eObjId, CObj* pObj)
{
    m_bDead = true;
    m_dwTime = GetTickCount64();
}