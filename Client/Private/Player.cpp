#include "stdafx.h"
#include "Player.h"
#include "DropItem.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "UiMgr.h"

extern float g_fVolume;
int g_iJumps = 0;
int g_iFalls = 0;

CPlayer::CPlayer() : m_bJump(false), m_fJumpSpeed(0.f), m_fJumpTime(0.f), m_ePreState(PS_END),
m_bLeftPressed(false), m_bRightPressed(false), m_bOnGround(true), m_bCharging(false),
m_fChargingValue(0.f), m_bJumping(false), m_bFalling(false), m_bWind(false), m_bIce(false),
m_bIsFlipped(false), m_dwTime(GetTickCount64())
{
    ZeroMemory(&m_tVelocity, sizeof(VECTOR2));
    ZeroMemory(&m_tForce, sizeof(VECTOR2));
}

CPlayer::~CPlayer()
{
    Release();
}

void CPlayer::Initialize()
{
    if (CObjMgr::Get_Instance()->Get_LoadPlayerPosition())
    {
        m_tInfo.fX = 0.f;
        m_tInfo.fY = 0.f;
        m_tInfo.fCX = 50.f;
        m_tInfo.fCY = 50.f;

        CObjMgr::Get_Instance()->LoadPlayerPosition(&m_tInfo.fX, &m_tInfo.fY);
    }
    else
        //m_tInfo = { 170.f, -3500.f, 50.f, 50.f };

    m_tInfo = { 78, 280, 50.f, 50.f };
    m_fSpeed = 5.f;
    m_tForce.fY = 0.5f;
    m_eCurState = PS_IDLE;
    m_eDir = DIR_RIGHT;
    m_eRender = GAMEOBJECT;

    m_fChargingValue = 0.f;
    m_fChargingValueDel = 0.5f;
    m_fChargingValueMin = 0.5f;
    m_fChargingValueMax = 20.f;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameNow = 0;
    m_tFrame.iFrameEnd = 6;
    m_tFrame.iMotion = 1;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount64();
   
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/Player_Left.bmp", L"Player_LEFT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/Player_Right.bmp", L"Player_RIGHT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/King_Crown_Left.bmp", L"Player_LEFT_Crown");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/King_Crown_Right.bmp", L"Player_RIGHT_Crown");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/KingShoes_Left.bmp", L"Player_LEFT_KingShoes");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/KingShoes_Right.bmp", L"Player_RIGHT_KingShoes");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/GiantBoots_Left.bmp", L"Player_LEFT_GiantBoots");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/GiantBoots_Right.bmp", L"Player_RIGHT_GiantBoots");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/CrownAndShoes_Left.bmp", L"Player_LEFT_CrownShoes");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/CrownAndShoes_Right.bmp", L"Player_RIGHT_CrownShoes");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/CrownAndGiantBoots_Left.bmp", L"Player_LEFT_CrownGiantBoots");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/sheets/CrownAndGiantBoots_Right.bmp", L"Player_RIGHT_CrownGiantBoots");


}

int CPlayer::Update()
{
    if (!g_bPause)
    { //방향키 조작
        Key_Input();

        //플레이어 애니메이션
        Motion_Change();

        ////////////////////// 아이템 기믹 효과 지속 시간;////////////////////////
        if (m_dwTime + 14000 < GetTickCount64())
        {
            m_bIsFlipped = false;
            m_dwTime = GetTickCount64();
        }
        ////////////////////////////////////////////////////////////////////////

        m_bMerchantCollision = CCollisionMgr::Get_Instance()->Collision_Shop(
            CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER),
            CObjMgr::Get_Instance()->Get_ObjList(OBJ_UI));

        __super::Update_Rect();
    }
    return OBJ_NOEVENT;
}


void CPlayer::Late_Update()
{
    if (!g_bPause)
    { //플레이어 점프, 이동등 움직임과 관련된 모든 함수
        Move();

        //플레이어 위치에 따른 화면 전환 스크롤
        float fScrollY = 0.f;
        if (m_tInfo.fY < 0)
        {
            fScrollY = LONG(-m_tInfo.fY / WINCY) * WINCY + WINCY;
        }
        CScrollMgr::Get_Instance()->Set_Scroll(0.f, fScrollY);

        __super::Move_Frame();
    }
}

void CPlayer::Render(HDC hDC)
{
    float   fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
    float   fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

    TCHAR szBuff[32] = { };
    _stprintf_s(szBuff, TEXT("fx : %f"), m_tInfo.fX);
    TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));

    TCHAR szBuff1[32] = { };
    _stprintf_s(szBuff1, TEXT("fy : %f"), m_tInfo.fY);
    TextOut(hDC, 50, 100, szBuff1, lstrlen(szBuff1));

    if (!CUiMgr::Get_Instance()->Get_Crown() && !CUiMgr::Get_Instance()->Get_KingShoes() && !CUiMgr::Get_Instance()->Get_GiantBoots())
    {
        if (m_eDir == DIR_LEFT)
            m_pFrameKey = L"Player_LEFT";
        else if (m_eDir == DIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT";

        if (m_eHDir == HDIR_LEFT)
            m_pFrameKey = L"Player_LEFT";
        else if (m_eHDir == HDIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT";

        HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
        GdiTransparentBlt(hDC, m_tRect.left + (long)fScrollX, m_tRect.top + (long)fScrollY,(int)m_tInfo.fCX,  (int)m_tInfo.fCY,hMemDC, m_tFrame.iFrameNow * (int)PLAYERCX,m_tFrame.iMotion * (int)PLAYERCY,(int)PLAYERCX,   (int)PLAYERCY,RGB(255, 0, 232));  
    }
    else if (CUiMgr::Get_Instance()->Get_Crown() && !CUiMgr::Get_Instance()->Get_KingShoes() && !CUiMgr::Get_Instance()->Get_GiantBoots())
    {
        if (m_eDir == DIR_LEFT)
            m_pFrameKey = L"Player_LEFT_Crown";
        else if (m_eDir == DIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_Crown";

        if (m_eHDir == HDIR_LEFT)
            m_pFrameKey = L"Player_LEFT_Crown";
        else if (m_eHDir == HDIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_Crown";

        HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
        GdiTransparentBlt(hDC, m_tRect.left + (long)fScrollX, m_tRect.top + (long)fScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, m_tFrame.iFrameNow * (int)PLAYERCX, m_tFrame.iMotion * (int)PLAYERCY, (int)PLAYERCX, (int)PLAYERCY, RGB(255, 0, 232));
    }
    else if (CUiMgr::Get_Instance()->Get_KingShoes() && !CUiMgr::Get_Instance()->Get_Crown() && !CUiMgr::Get_Instance()->Get_GiantBoots())
    {
        if (m_eDir == DIR_LEFT)
            m_pFrameKey = L"Player_LEFT_KingShoes";
        else if (m_eDir == DIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_KingShoes";

        if (m_eHDir == HDIR_LEFT)
            m_pFrameKey = L"Player_LEFT_KingShoes";
        else if (m_eHDir == HDIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_KingShoes";

        HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
        GdiTransparentBlt(hDC, m_tRect.left + (long)fScrollX, m_tRect.top + (long)fScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, m_tFrame.iFrameNow * (int)PLAYERCX, m_tFrame.iMotion * (int)PLAYERCY, (int)PLAYERCX, (int)PLAYERCY, RGB(255, 0, 232));
    }
    else if (CUiMgr::Get_Instance()->Get_GiantBoots() && !CUiMgr::Get_Instance()->Get_KingShoes() && !CUiMgr::Get_Instance()->Get_Crown())
    {
        if (m_eDir == DIR_LEFT)
            m_pFrameKey = L"Player_LEFT_GiantBoots";
        else if (m_eDir == DIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_GiantBoots";

        if (m_eHDir == HDIR_LEFT)
            m_pFrameKey = L"Player_LEFT_GiantBoots";
        else if (m_eHDir == HDIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_GiantBoots";

        HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
        GdiTransparentBlt(hDC, m_tRect.left + (long)fScrollX, m_tRect.top + (long)fScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, m_tFrame.iFrameNow * (int)PLAYERCX, m_tFrame.iMotion * (int)PLAYERCY, (int)PLAYERCX, (int)PLAYERCY, RGB(255, 0, 232));
    }
    else if (CUiMgr::Get_Instance()->Get_KingShoes() && CUiMgr::Get_Instance()->Get_Crown())
    {
        if (m_eDir == DIR_LEFT)
            m_pFrameKey = L"Player_LEFT_CrownShoes";
        else if (m_eDir == DIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_CrownShoes";

        if (m_eHDir == HDIR_LEFT)
            m_pFrameKey = L"Player_LEFT_CrownShoes";
        else if (m_eHDir == HDIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_CrownShoes";

        HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
        GdiTransparentBlt(hDC, m_tRect.left + (long)fScrollX, m_tRect.top + (long)fScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, m_tFrame.iFrameNow * (int)PLAYERCX, m_tFrame.iMotion * (int)PLAYERCY, (int)PLAYERCX, (int)PLAYERCY, RGB(255, 0, 232));
    }
    else if (CUiMgr::Get_Instance()->Get_GiantBoots() && CUiMgr::Get_Instance()->Get_Crown())
    {
        if (m_eDir == DIR_LEFT)
            m_pFrameKey = L"Player_LEFT_CrownGiantBoots";
        else if (m_eDir == DIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_CrownGiantBoots";

        if (m_eHDir == HDIR_LEFT)
            m_pFrameKey = L"Player_LEFT_CrownGiantBoots";
        else if (m_eHDir == HDIR_RIGHT)
            m_pFrameKey = L"Player_RIGHT_CrownGiantBoots";

        HDC   hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
        GdiTransparentBlt(hDC, m_tRect.left + (long)fScrollX, m_tRect.top + (long)fScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, m_tFrame.iFrameNow * (int)PLAYERCX, m_tFrame.iMotion * (int)PLAYERCY, (int)PLAYERCX, (int)PLAYERCY, RGB(255, 0, 232));
    }
    
    HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

    HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

    Rectangle(hDC, m_tRect.left, m_tRect.top + (long)fScrollY, m_tRect.right, m_tRect.bottom + (long)fScrollY);

    SelectObject(hDC, hOldPen);
    DeleteObject(hNewPen);

    SelectObject(hDC, oldBrush);
    DeleteObject(myBrush);


    //1스테이지 FG
    HDC		h1StageFG1DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_FG1");
    GdiTransparentBlt(hDC, 0, 0+fScrollY,WINCX, WINCY, h1StageFG1DC,0, 0,WINCX, WINCY, RGB(255, 0, 232));
    HDC		h1StageFG2DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_FG2");
    GdiTransparentBlt(hDC, 0, fScrollY - WINCY, WINCX, WINCY, h1StageFG2DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));
    HDC		h1StageFG3DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_FG3");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 2, WINCX, WINCY, h1StageFG3DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));
    HDC		h1StageFG4DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_FG4");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 3, WINCX, WINCY, h1StageFG4DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));
    HDC		h1StageFG5DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_FG5");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 4, WINCX, WINCY, h1StageFG5DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));

    //2스테이지
    HDC		h2StageFG1DC = CBmpMgr::Get_Instance()->Find_Img(L"Second_Stage_FG1");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 5, WINCX, WINCY, h2StageFG1DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));
    HDC		h2StageFG2DC = CBmpMgr::Get_Instance()->Find_Img(L"Second_Stage_FG2");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 6, WINCX, WINCY, h2StageFG2DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));

    //3스테이지
    HDC		h3StageFG3DC = CBmpMgr::Get_Instance()->Find_Img(L"Third_Stage_FG1");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 7, WINCX, WINCY, h3StageFG3DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));

    //4스테이지
    HDC		h4StageFG1DC = CBmpMgr::Get_Instance()->Find_Img(L"Fourth_Stage_FG1");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 8, WINCX, WINCY, h4StageFG1DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));
    HDC		h4StageFG2DC = CBmpMgr::Get_Instance()->Find_Img(L"Fourth_Stage_FG2");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 9, WINCX, WINCY, h4StageFG2DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));

    //5스테이지
    HDC		h5StageFG3DC = CBmpMgr::Get_Instance()->Find_Img(L"End_Stage_FG1");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 10, WINCX, WINCY, h5StageFG3DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));
    HDC		h5StageFG4DC = CBmpMgr::Get_Instance()->Find_Img(L"End_Stage_FG2");
    GdiTransparentBlt(hDC, 0, (int)fScrollY - WINCY * 11, WINCX, WINCY, h5StageFG4DC, 0, 0, WINCX, WINCY, RGB(255, 0, 232));
}

void CPlayer::Release()
{

}

void CPlayer::Key_Input(void)
{
    //윗 방향키를 누르면 다음 씬으로 전환
    if (m_bTeleportCollision)
    {
        if (CKeyMgr::Get_Instance()->Key_Down(VK_UP) /*&& (m_bTeleportCollision)*/)
        {
            m_bTeleportCollision = CCollisionMgr::Get_Instance()->Collision_Teleport(
                CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER),
                CObjMgr::Get_Instance()->Get_ObjList(OBJ_TELEPORT));

            if (m_bTeleportCollision)
            {
                TeleportToAnotherScene();
            }

        }
    }

     if (!m_bOnGround)
         return;
    
     m_bRightPressed = false;
     m_bLeftPressed = false;

     //아무것도 안눌렀을때
     if (!GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_SPACE) && !GetAsyncKeyState(VK_RIGHT))
     {
    
         if (m_eCurState != PS_DEAD && m_eCurState != PS_MONSTER_HIT)
             m_eCurState = PS_IDLE;
     }

     //오른쪽 방향키만 눌렀을때
     if (GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_SPACE) && !m_bGotHit)
     {
         if (m_bIsFlipped)
         {
             m_bLeftPressed = true;
             m_eDir = DIR_RIGHT;
             m_eCurState = PS_WALK;
         }
         else
         {
             m_bRightPressed = true;
             m_eDir = DIR_RIGHT;
             m_eCurState = PS_WALK;
         }
     }

     //왼쪽 방향키만 눌렀을때
     if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_SPACE) && !m_bGotHit)
     {
         if (m_bIsFlipped)
         {
             m_bRightPressed = true;
             m_eDir = DIR_LEFT;
             m_eCurState = PS_WALK;
         }
         else
         {
             m_bLeftPressed = true;
             m_eDir = DIR_LEFT;
             m_eCurState = PS_WALK;
         }
     }

     //스페이스바를 눌렀을때
     if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
     {
         if (GetAsyncKeyState(VK_LEFT))
         {
             m_tVelocity.fX -= 1;
             m_eDir = DIR_LEFT;
         }
         else if (GetAsyncKeyState(VK_RIGHT))
         {
             m_tVelocity.fX += 1;
             m_eDir = DIR_RIGHT;
         }
         else if (!GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT))
         {
             m_tVelocity.fX = 0;
             m_eDir = DIR_UP;
         }
         m_bCharging = true;
         m_eCurState = PS_CHARGING;
     }
    
     // charging 중일 때
     if (m_bCharging)
     {
         m_fChargingValue += m_fChargingValueDel; // 원하는 charging 속도로 값을 증가시킴
         if (m_fChargingValue > m_fChargingValueMax)
         {
             m_fChargingValue = m_fChargingValueMax;
    
             m_bCharging = false;
             m_tVelocity.fY = -m_fChargingValue;
             if (m_eDir != DIR_UP)
             {
                 m_tVelocity.fX = m_eDir == DIR_LEFT ? -6.5f : 6.5f;
             }
             m_fChargingValue = 0.f; // charging 값을 초기화
             m_bOnGround = false; // 점프 시작
             m_eCurState = PS_JUMPING;
             g_iJumps++;

             CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
             CSoundMgr::Get_Instance()->PlaySound(L"king_jump.wav", SOUND_EFFECT, g_fVolume);

         }

     }
    
     //Space 키를 떼면 charging 멈추고 m_tVelocity.fY에 반영
     if (!GetAsyncKeyState(VK_SPACE) && m_bCharging)
     {
         if (m_fChargingValue < m_fChargingValueMin)
             m_fChargingValue = m_fChargingValueMin;
    
         m_bCharging = false;
         m_tVelocity.fY = -m_fChargingValue;
         if (m_eDir != DIR_UP)
         {
             m_tVelocity.fX = m_eDir == DIR_LEFT ? -6.5f : 6.5f;
         }
         m_fChargingValue = 0.f; // charging 값을 초기화
         m_bOnGround = false; // 점프 시작
         m_eCurState = PS_JUMPING;
         g_iJumps++;

         CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
         CSoundMgr::Get_Instance()->PlaySound(L"king_jump.wav", SOUND_EFFECT, g_fVolume);

     }

     if (m_bMerchantCollision)
     {
         if (!CUiMgr::Get_Instance()->Get_Merchant() && CKeyMgr::Get_Instance()->Key_Down(VK_UP))
         {
             CUiMgr::Get_Instance()->Set_Merchant(true);
             CUiMgr::Get_Instance()->Set_YesOrNo();
         }
     }
     else if(CUiMgr::Get_Instance()->Get_Merchant())
     {
         CUiMgr::Get_Instance()->Set_Merchant(false);
         CUiMgr::Get_Instance()->Set_YesOrNo();
     }
}

void CPlayer::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case PS_IDLE:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameNow = 0;
            m_tFrame.iFrameEnd = 6;
            m_tFrame.iMotion = 1;
            m_tFrame.dwSpeed = 600;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PS_WALK:
            m_tFrame.iFrameStart = 1;
            m_tFrame.iFrameNow = 1;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 150;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PS_CHARGING:
            m_tFrame.iFrameStart = 4;
            m_tFrame.iFrameNow = 4;
            m_tFrame.iFrameEnd = 4;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PS_JUMPING:
            m_tFrame.iFrameStart = 5;
            m_tFrame.iFrameNow = 5;
            m_tFrame.iFrameEnd = 6;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 400;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PS_HIT:
            m_tFrame.iFrameStart = 8;
            m_tFrame.iFrameNow = 8;
            m_tFrame.iFrameEnd = 8;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 100;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PS_MONSTER_HIT:
            m_bGotHit = true;
            m_tFrame.iFrameStart = 8;
            m_tFrame.iFrameNow = 8;
            m_tFrame.iFrameEnd = 8;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 1000;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PS_DEAD:
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
void CPlayer::Move()
{
    float   fY = 0.f;
    LINE_TYPE eGroundLT = LT_NONE;
    LINE_SHAPE eGroundLS = LS_NONE;

    bool bGroundCol = CCollisionMgr::Get_Instance()->Collision_Ground(&fY, m_tInfo, &eGroundLT, &eGroundLS);
    int iMonsterRectCol = CCollisionMgr::Get_Instance()->Collision_RectEx(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER),
        CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));

    // 착지했을때
    if (m_bOnGround)
    {

        if (bGroundCol == false || m_tInfo.fY < fY - m_tInfo.fCY)
        {
            m_tInfo.fX += m_tVelocity.fX;
            m_bOnGround = false;
            return;
        }
        else
            m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
       
        
        if (false == m_bGotHit)
        {
            switch (eGroundLT)
            {
            case LT_NORMAL:
                switch (eGroundLS)
                {
                case LS_LEFT_WALL:
                    // m_tVelocity.fX = 0;
                    break;
                case LS_RIGHT_WALL:
                    //m_tVelocity.fX = 0;
                    break;
                case LS_LEFT_DIAGONAL:
                    m_tVelocity.fX -= 0.25f;
                    break;
                case LS_RIGHT_DIAGONAL:
                    m_tVelocity.fX += 0.25f;
                    break;
                case LS_GROUND:
                    m_tVelocity.fX = 0;
                    break;
                }
                if (m_bLeftPressed && m_tVelocity.fX > -3.f)
                    m_tVelocity.fX -= 3.5f;
                else if (m_bRightPressed && m_tVelocity.fX < 3.f)
                    m_tVelocity.fX += 3.5f;
                break;
            case LT_ICE:
                switch (eGroundLS)
                {
                case LS_GROUND:
                    break;
                case LS_LEFT_DIAGONAL:
                    break;
                case LS_RIGHT_DIAGONAL:
                    break;
                }
                break;
            }

        }
        else
        {

        }
      
        m_tVelocity.fY = 0;
        float fNextX = m_tInfo.fX + m_tVelocity.fX;

        DIRECTION eDirColHor(DIR_NONE);
        VECTOR2 tColPointHor{ 0.f, 0.f };
        INFO tCheckInfoHor(m_tInfo);

        if (m_tVelocity.fX > 0)
            tCheckInfoHor.fX += m_tInfo.fCX * 0.5f;
        else if (m_tVelocity.fX < 0)
            tCheckInfoHor.fX -= m_tInfo.fCX * 0.5f;

        bool bHorizontalLineCol = CCollisionMgr::Get_Instance()->Collision_Line_Horizontal(tCheckInfoHor,m_tVelocity,&tColPointHor,&eDirColHor);

        if (eDirColHor != DIR_RIGHT && eDirColHor != DIR_LEFT)
            m_tInfo.fX = fNextX;

        /*if (bGroundCol == false || m_tInfo.fY < fY - m_tInfo.fCY)
            m_bOnGround = false;*//*
        else
            m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;*/

        //////////////////////넉백기믹///////////////////////
        if (iMonsterRectCol == CR_LEFT || iMonsterRectCol == CR_RIGHT || iMonsterRectCol == CR_UP)
        {
            if (iMonsterRectCol == CR_LEFT)
            {
                m_eCurState = PS_MONSTER_HIT;
                m_eHDir = HDIR_RIGHT;
            }
            else if (iMonsterRectCol == CR_RIGHT)
            {
                m_eCurState = PS_MONSTER_HIT;
                m_eHDir = HDIR_LEFT;
            }
            else
            {
                m_eCurState = PS_MONSTER_HIT;
            }
        }
        ///////////////////////////////////////////////////
    }
    else //점프중
    {
        // 중력 등 바깥 요소에 의해 속도가 바뀜
        m_tVelocity.fY += m_tForce.fY;//아래로 잡아 당기는 중력

        /////////////////////////////////////////바람 관련된 힘//////////////////////////////////////
        //float fWindForce = m_tForce.fX + 0.2f;
        ////바람맵때 사용할 로직
        //if (m_tInfo.fY < -600)
        //{
        //    if (m_bWind)
        //    {
        //        m_tVelocity.fX += fWindForce;
        //        
        //        if (m_dwTime + 5000 < GetTickCount64())
        //        {
        //            m_bWind = false;
        //            m_dwTime = GetTickCount64();
        //        }
        //    }
        //    if (!m_bWind)
        //    {
        //        m_tVelocity.fX -= fWindForce;

        //        if (m_dwTime + 5000 < GetTickCount64())
        //        {
        //            m_bWind = true;
        //            m_dwTime = GetTickCount64();
        //        }
        //    }
        //}
        //else
        //{
        //    m_tVelocity.fX += m_tForce.fX;
        //}
        ////////////////////////////////////////////////////////////////////////////

        m_tVelocity.fX += m_tForce.fX;//좌우 바람들 영향을 주는 힘


        DIRECTION eDirColHor(DIR_NONE);
        DIRECTION eDirColVer(DIR_NONE);
        VECTOR2 tColPointHor{ 0.f, 0.f };
        VECTOR2 tColPointVer{ 0.f, 0.f };
        INFO tCheckInfoHor(m_tInfo);
        INFO tCheckInfoVer(m_tInfo);

        //오른쪽으로
        if (m_tVelocity.fX > 0)
            tCheckInfoHor.fX += m_tInfo.fCX * 0.5f;
        //왼쪽으로
        else if ((m_tVelocity.fX < 0))
            tCheckInfoHor.fX -= m_tInfo.fCX * 0.5f;
        //위로
        if ((m_tVelocity.fY < 0))
            tCheckInfoVer.fY -= m_tInfo.fCY * 0.5f;
        //아래로
        else if (m_tVelocity.fY > 0)
            tCheckInfoVer.fY += m_tInfo.fCY * 0.5f;

        bool bLineColHor = CCollisionMgr::Get_Instance()->Collision_Line_Horizontal(tCheckInfoHor,m_tVelocity,&tColPointHor,&eDirColHor);
        bool bLineColVer = CCollisionMgr::Get_Instance()->Collision_Line_Vertical(tCheckInfoVer,m_tVelocity,&tColPointVer,&eDirColVer);

        // 속도로 다음 위치를 구해줌
        float fNextX = m_tInfo.fX + m_tVelocity.fX;
        float fNextY = m_tInfo.fY + m_tVelocity.fY;

        if (bLineColVer)
        {
            /*if (eDirColVer == DIR_DOWN)
            {
               if (m_tVelocity.fY > 20)
               {
                  m_eCurState = PS_DEAD;
                  CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                  CSoundMgr::Get_Instance()->PlaySound(L"king_splat.wav", SOUND_EFFECT, g_fVolume);
               }
               m_tVelocity.fY = 0;
               m_tVelocity.fX = 0;

               fNextY = tColPointVer.fY - m_tInfo.fCY * 0.5f;

               m_bLanding = true;
            }*/
            ///////////////////////////////////얼음 맵///////////////////////////////////////////////////
            if (eDirColVer == DIR_DOWN)
            {
                if (m_tVelocity.fY > 20)
                {
                    m_eCurState = PS_DEAD; 
                    g_iFalls++;
                    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                    CSoundMgr::Get_Instance()->PlaySound(L"king_splat.wav", SOUND_EFFECT, g_fVolume);
                }
                else
                {
                   CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                    CSoundMgr::Get_Instance()->PlaySound(L"king_land.wav", SOUND_EFFECT, g_fVolume);
                }
           
                m_tVelocity.fY = 0;
                m_tVelocity.fX = 0;

                fNextY = tColPointVer.fY - m_tInfo.fCY * 0.5f;

                /*if (bGroundCol == false || m_tInfo.fY < fY - m_tInfo.fCY)
                {
                    m_tInfo.fX += m_tVelocity.fY;
                    m_bOnGround = false;
                }*/
                //else
                //    m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
                m_bOnGround = true;

            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            else if (eDirColVer == DIR_UP)
            {
                CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                CSoundMgr::Get_Instance()->PlaySound(L"king_bump.wav", SOUND_EFFECT, g_fVolume);
                fNextY = tColPointVer.fY + m_tInfo.fCY * 0.5f;
                m_tVelocity.fY = -0.2 * m_tVelocity.fY;
                m_eCurState = PS_HIT;
            }
        }

        if (bLineColHor)
        {
            if (eDirColHor == DIR_LEFT)
            {
                CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                CSoundMgr::Get_Instance()->PlaySound(L"king_bump.wav", SOUND_EFFECT, g_fVolume);
                fNextX = tColPointHor.fX + m_tInfo.fCX * 0.5f;
                m_tVelocity.fX = -0.5f * m_tVelocity.fX;
                m_eCurState = PS_HIT;

                m_eDir = DIR_LEFT;
            }
            else if (eDirColHor == DIR_RIGHT)
            {
                CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                CSoundMgr::Get_Instance()->PlaySound(L"king_bump.wav", SOUND_EFFECT, g_fVolume);
                fNextX = tColPointHor.fX - m_tInfo.fCX * 0.5f;
                m_tVelocity.fX = -0.5f * m_tVelocity.fX;
                m_eCurState = PS_HIT;

                m_eDir = DIR_RIGHT;
            }
        }

        m_tInfo.fX = fNextX;
        m_tInfo.fY = fNextY;
    }

}

void CPlayer::TeleportToAnotherScene()
{
    if (m_bTeleportCollision)
    {
        if (m_eTT == TT_TELEPORT_GOUP)
        {
            //if(CObj)
            Set_Pos(74.f, -1150.f);
            m_eTT = TT_END;
            m_bTeleportCollision = false;
        }
        else if (m_eTT == TT_TELEPORT_GODOWN)
        {
            //if (CObj)
            Set_Pos(355.f, 520.f);
            m_eTT = TT_END;
            m_bTeleportCollision = false;
        }
    }
}

void CPlayer::TouchLine(const LineInfo& lineInfo)
{
    m_tLineInfo = lineInfo;
}

void CPlayer::Collision(OBJ_ID eObjId, CObj* pObj)
{
    switch (eObjId)
    {
    case OBJ_DROPITEM:
        switch (pObj->Get_ItemType())
        {
        case IT_THUNDER:
            m_bIsFlipped = true;
            break;
        }
        break;
    }
}