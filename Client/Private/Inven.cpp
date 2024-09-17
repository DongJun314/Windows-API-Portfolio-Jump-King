#include "stdafx.h"
#include "Inven.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CInven::CInven()
{
}

CInven::~CInven()
{
    Release();
}

void CInven::Initialize()
{
    m_eRender = UI;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/frameEnd.bmp", L"Inven");
 
}

int CInven::Update()
{
    Key_Input();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CInven::Late_Update()
{
}

void CInven::Render(HDC hDC)
{
    float   fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hInvenDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
    GdiTransparentBlt(hDC, 410, 41,
        220, 165, hInvenDC,
        m_tFrame.iFrameNow * 220, m_tFrame.iMotion * 165,
        220, 165, RGB(255, 255, 255));

   /* HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
    GdiTransparentBlt(hDC, 422, m_fYesOrNoCursorY,
        22, 22, hCursor1DC,
        m_tFrame.iFrameNow * 11, m_tFrame.iMotion * 11,
        11, 11, RGB(255, 0, 232));*/
}

void CInven::Key_Input(void)
{
 
}

void CInven::Release()
{
}
