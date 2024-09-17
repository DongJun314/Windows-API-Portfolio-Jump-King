#include "stdafx.h"
#include "Shop.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CShop::CShop()
{
}

CShop::~CShop()
{
    Release();
}

void CShop::Initialize()
{
    m_eRender = BG;
    m_eCurState = MS_MERCHANT;
    m_pFrameKey = L"merchant";

    m_tFrame.iFrameStart = 2;
    m_tFrame.iFrameNow = 2;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 300;
    m_tFrame.dwTime = GetTickCount64();

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/props/merchant.bmp", L"merchant");
   // CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/props/Annie.bmp", L"merchant");
}

int CShop::Update()
{
    if (!g_bPause)
    {

        __super::Update_Rect();
    }
    return OBJ_NOEVENT;
}

void CShop::Late_Update()
{
    if (!g_bPause)
    {
        __super::Move_Frame();
    }
}

void CShop::Render(HDC hDC)
{
    float   fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

    GdiTransparentBlt(hDC,
        m_tRect.left,
        m_tRect.top + (long)fScrollY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,			// 비트맵을 가지고 있는 DC 전달
        m_tFrame.iFrameNow * 64,
        m_tFrame.iMotion * 64,
        64,   // 복사할 비트맵의 가로, 세로 사이즈
        64,
        RGB(255, 0, 232));

    //GdiTransparentBlt(hDC,
    //    m_tRect.left,
    //    m_tRect.top + (long)fScrollY,
    //    (int)m_tInfo.fCX,
    //    (int)m_tInfo.fCY,
    //    hMemDC,			// 비트맵을 가지고 있는 DC 전달
    //    m_tFrame.iFrameNow * 160,
    //    m_tFrame.iMotion * 100,
    //    160,   // 복사할 비트맵의 가로, 세로 사이즈
    //    100,
    //    RGB(255, 0, 232));

    HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

    HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

    Rectangle(hDC, m_tRect.left, m_tRect.top + (long)fScrollY, m_tRect.right, m_tRect.bottom + (long)fScrollY);

    SelectObject(hDC, hOldPen);
    DeleteObject(hNewPen);

    SelectObject(hDC, oldBrush);
    DeleteObject(myBrush);
}

void CShop::Release()
{
}

void CShop::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case MS_MERCHANT:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameNow = 0;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 800;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }

        m_ePreState = m_eCurState;
    }
}

