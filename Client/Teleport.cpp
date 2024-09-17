#include "stdafx.h"
#include "Teleport.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CTeleport::CTeleport()
{
}

CTeleport::~CTeleport()
{
    Release();
}

void CTeleport::Initialize()
{
    m_eRender = BG;
    m_eCurState = DIS_TELEPORT;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameNow = 0;
    m_tFrame.iFrameEnd = 7;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Teleport.bmp", L"Teleport");
}

int CTeleport::Update()
{
    if (!g_bPause)
    {
        Motion_Change();

        __super::Update_Rect();
    }
    return OBJ_NOEVENT;
}

void CTeleport::Late_Update()
{
    if (!g_bPause)
    {
        __super::Move_Frame();
    }
}

void CTeleport::Render(HDC hDC)
{
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC   hMemTeleport1DC = CBmpMgr::Get_Instance()->Find_Img(L"Teleport");
    GdiTransparentBlt(hDC,         // ���� ����(���������� �׸��� �׸�) DC�� ����
        m_tRect.left, // ���� ���� ��ġ�� ��ǥ�� ���� (x,y ��ǥ)
        m_tRect.top + (long)iScrollY,
        (int)m_tInfo.fCX,   // ���� ���� ����, ���� ����
        (int)m_tInfo.fCY,
        hMemTeleport1DC,         // ��Ʈ���� ������ �ִ� DC ����
        m_tFrame.iFrameNow * 50,
        m_tFrame.iMotion * 50,
        50,   // ������ ��Ʈ���� ����, ���� ������
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

void CTeleport::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case DIS_TELEPORT:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameNow = 0;
            m_tFrame.iFrameEnd = 7;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 100;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }

        m_ePreState = m_eCurState;
    }
}

void CTeleport::Release()
{
}
