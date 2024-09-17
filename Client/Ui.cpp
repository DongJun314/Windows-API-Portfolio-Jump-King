#include "stdafx.h"
#include "Ui.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UiMgr.h"
#include "ObjMgr.h"

extern int g_iJumps;
extern int g_iFalls;
DWORD g_dStartTime;

CUi::CUi()
    : m_iResumeX(590), m_iInvenX(590), m_iOptionsX(590), m_iSaveExitX(590),
    m_iGiveUpX(590), m_iAreYouSure(440), m_iNo(440), m_iYes(440),
    m_iPreCursorIndex(0), m_iCrown(440), m_iKingShoes(440), m_iGaintBoots(440), m_iBack(440),
    m_bCrown(false), m_bKingShoes(false), m_bGaintBoots(false), m_iCrownInShop(590), m_iKingShoesInShop(590),
    m_iGaintBootsInShop(590),m_bCrownInShop(false), m_bKingShoesInShop(false), m_bGaintBootsInShop(false),
    m_fMerchantCursorY(72.f)
{
}

CUi::~CUi()
{
    Release();
}

void CUi::Initialize()
{
    g_dStartTime = GetTickCount();
    m_eRender = UI;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/setting_menu.bmp", L"setting_menu");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/frameEnd.bmp", L"frameEnd");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/frameInven.bmp", L"Inven");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/cursor.bmp", L"cursor");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/back.bmp", L"back");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/checkbox1.bmp", L"checkbox1");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/checkbox2.bmp", L"checkbox2");

}

int CUi::Update()
{

    if (CUiMgr::Get_Instance()->Get_Merchant())
    {
        if (CUiMgr::Get_Instance()->Get_MerchantCursorIndex() == 0)
        {
            m_fMerchantCursorY = 75.f;
            m_iCrownInShop = 602;
        }
        else
            m_iCrownInShop = 590;

        if (CUiMgr::Get_Instance()->Get_MerchantCursorIndex() == 1)
        {
            m_fMerchantCursorY = 116.f;
            m_iKingShoesInShop = 602;
        }
        else
            m_iKingShoesInShop = 590;

        if (CUiMgr::Get_Instance()->Get_MerchantCursorIndex() == 2)
        {
            m_fMerchantCursorY = 158.f;
            m_iGaintBootsInShop = 602;
        }
        else
            m_iGaintBootsInShop = 590;

        if (CUiMgr::Get_Instance()->Get_MerchantCursorIndex() == 3)
        {
            m_fMerchantCursorY = 200.f;
            m_iBack = 597;
        }
        else
            m_iBack = 585;
    }

    if (!CUiMgr::Get_Instance()->Get_YesOrNo()/* && !CUiMgr::Get_Instance()->Get_Merchant()*/)
    {
        if (CUiMgr::Get_Instance()->Get_CursorIndex() == 0)
        {
            m_fCursorY = 66.f;
            m_iResumeX = 602;
        }
        else
            m_iResumeX = 590;

        if (CUiMgr::Get_Instance()->Get_CursorIndex() == 1)
        {
            m_fCursorY = 102.f;
            m_iInvenX = 602;
        }
        else
            m_iInvenX = 590;

        if (CUiMgr::Get_Instance()->Get_CursorIndex() == 2)
        {
            m_fCursorY = 139.f;
            m_iOptionsX = 602;
        }
        else
            m_iOptionsX = 590;

        if (CUiMgr::Get_Instance()->Get_CursorIndex() == 3)
        {
            m_fCursorY = 175.f;
            m_iSaveExitX = 602;
        }
        else
            m_iSaveExitX = 590;

        if (CUiMgr::Get_Instance()->Get_CursorIndex() == 4)
        {
            m_fCursorY = 212.f;
            m_iGiveUpX = 602;
        }
        else
            m_iGiveUpX = 590;
    }

    return 0;
}

void CUi::Late_Update()
{
    if (CUiMgr::Get_Instance()->Get_YesOrNo())
    {
        if (CUiMgr::Get_Instance()->Get_YesOrNoCursorIndex() == 0)
        {
            m_fYesOrNoCursorY = 112.f;
            m_iNo = 452;
        }
        else
            m_iNo = 440;

        if (CUiMgr::Get_Instance()->Get_YesOrNoCursorIndex() == 1)
        {
            m_fYesOrNoCursorY = 155.f;
            m_iYes = 452;
        }
        else
            m_iYes = 440;
    }

    if (CUiMgr::Get_Instance()->Get_Inventory())
    {
        if (CUiMgr::Get_Instance()->Get_InvenCursorIndex() == 0)
        {
            m_fInvenCursorY = 72.f;
            m_iCrown = 452;
        }
        else
            m_iCrown = 440;

        if (CUiMgr::Get_Instance()->Get_InvenCursorIndex() == 1)
        {
            m_fInvenCursorY = 113.f;
            m_iKingShoes = 452;
        }
        else
            m_iKingShoes = 440;

        if (CUiMgr::Get_Instance()->Get_InvenCursorIndex() == 2)
        {
            m_fInvenCursorY = 155.f;
            m_iGaintBoots = 452;
        }
        else
            m_iGaintBoots = 440;

        if (CUiMgr::Get_Instance()->Get_InvenCursorIndex() == 3)
        {
            m_fInvenCursorY = 190.f;
            m_iBack = 452;
        }
        else
            m_iBack = 440;
    }

}

void CUi::Render(HDC hDC)
{ 
    ///////////////////////////////////////////상점////////////////////////////////////
    if (CUiMgr::Get_Instance()->Get_Merchant())
    {
        if (CUiMgr::Get_Instance()->Get_CheckWhetherPressedMerchant())
        {
            HDC	hUiForMerchantDC = CBmpMgr::Get_Instance()->Find_Img(L"setting_menu");
            GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hUiForMerchantDC, m_tFrame.iFrameNow * 800, m_tFrame.iMotion * 600, WINCX, WINCY, RGB(255, 255, 255));
            HDC	hCursor2DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
            GdiTransparentBlt(hDC, 570.f, m_fMerchantCursorY, 22, 22, hCursor2DC, m_tFrame.iFrameNow * 11, m_tFrame.iMotion * 11, 11, 11, RGB(255, 0, 232));
            
            if (CUiMgr::Get_Instance()->Get_Merchant_Crown())
            {
                swprintf_s(m_szText, L"Crown");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iCrownInShop, 75, L"LitterLover2", TA_LEFT, RGB(0, 255, 0));
            }
            else
            {
                swprintf_s(m_szText, L"Crown");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iCrownInShop, 75, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
            }
            
            if (CUiMgr::Get_Instance()->Get_Merchant_KingShoes())
            {
                swprintf_s(m_szText, L"King Shoes");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iKingShoesInShop, 116, L"LitterLover2", TA_LEFT, RGB(0, 255, 0));
            }
            else
            {
                swprintf_s(m_szText, L"King Shoes");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iKingShoesInShop, 116, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
            }

            if (CUiMgr::Get_Instance()->Get_Merchant_GiantBoots())
            {
                swprintf_s(m_szText, L"Giant Boots");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iGaintBootsInShop, 158, L"LitterLover2", TA_LEFT, RGB(0, 255, 0));
            }
            else
            {
                swprintf_s(m_szText, L"Giant Boots");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iGaintBootsInShop, 158, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
            }

            HDC	hBack1DC = CBmpMgr::Get_Instance()->Find_Img(L"back");
            GdiTransparentBlt(hDC, m_iBack, 200, 32, 28, hBack1DC, m_tFrame.iFrameNow * 16, m_tFrame.iMotion * 14, 16, 14, RGB(255, 0, 232));

            swprintf_s(m_szText, L"OBJECTIVE: GET TO THE BABE AT THE TOP!");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 400, 541, L"LitterLover2", TA_CENTER, RGB(255, 255, 255));

            swprintf_s(m_szText, L"Welcome to our store!!");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 32, 240, 80, L"LitterLover2", TA_CENTER, RGB(255, 255, 255));

            swprintf_s(m_szText, L"If you need any help,");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 20, 240, 117, L"LitterLover2", TA_CENTER, RGB(255, 255, 255));

            swprintf_s(m_szText, L" feel free to ask.");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 20, 240, 140, L"LitterLover2", TA_CENTER, RGB(255, 255, 255));
          
            swprintf_s(m_szText, L" What would you like to buy ?");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 23, 240, 188, L"LitterLover2", TA_CENTER, RGB(255, 255, 255));
           
            if (CUiMgr::Get_Instance()->Get_YesOrNo())
            {
                HDC	hEndDC = CBmpMgr::Get_Instance()->Find_Img(L"frameEnd");
                GdiTransparentBlt(hDC, 410, 41, 220, 165, hEndDC, m_tFrame.iFrameNow * 220, m_tFrame.iMotion * 165, 220, 165, RGB(255, 255, 255));
                HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
                GdiTransparentBlt(hDC, 422, m_fYesOrNoCursorY, 22, 22, hCursor1DC, m_tFrame.iFrameNow * 11, m_tFrame.iMotion * 11, 11, 11, RGB(255, 0, 232));

                swprintf_s(m_szText, L"ARE YOU SURE?");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iAreYouSure, 68, L"LitterLover2", TA_LEFT, RGB(255, 0, 0));
                swprintf_s(m_szText, L"YES");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iNo, 112, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
                swprintf_s(m_szText, L"NO");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iYes, 155, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));

                if (CUiMgr::Get_Instance()->Get_BackToPrevious())
                {
                    CUiMgr::Get_Instance()->Set_YesOrNo();
                    CUiMgr::Get_Instance()->Set_BackToPrevious();
                }
                else if (CUiMgr::Get_Instance()->Get_DestroyWindow())
                {
                    CUiMgr::Get_Instance()->Set_YesOrNo();
                    CUiMgr::Get_Instance()->Set_DestroyWindow();
                }
            }
        }
    }

    if (g_bPause)
    {
         //esc를 누르고 나온 맨처음 설정메뉴
         HDC	hUiDC = CBmpMgr::Get_Instance()->Find_Img(L"setting_menu");
         GdiTransparentBlt(hDC, 0, 0,WINCX, WINCY, hUiDC,m_tFrame.iFrameNow * 800, m_tFrame.iMotion * 600,WINCX, WINCY, RGB(255, 255, 255));
         HDC	hCursorDC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
         GdiTransparentBlt(hDC, 570.f, m_fCursorY,22, 22, hCursorDC,m_tFrame.iFrameNow * 11, m_tFrame.iMotion * 11,11, 11, RGB(255, 0, 232));

         swprintf_s(m_szText, L"RESUME");
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iResumeX, 67, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
         swprintf_s(m_szText, L"INVENTORY");
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iInvenX, 103, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
         swprintf_s(m_szText, L"OPTIONS");
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iOptionsX, 140, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
         swprintf_s(m_szText, L"SAVE & EXIT");
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iSaveExitX, 176, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
         swprintf_s(m_szText, L"GIVE UP");
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iGiveUpX, 213, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
         swprintf_s(m_szText, L"OBJECTIVE: GET TO THE BABE AT THE TOP!");
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 400, 541, L"LitterLover2", TA_CENTER, RGB(255, 255, 255));

         int iAttemp = 1;

         DWORD dCurrentTime = GetTickCount(); // 현재 시간을 가져옴
         DWORD dElapsedTime = dCurrentTime - g_dStartTime; // 경과한 시간을 밀리초로 계산

         // 경과 시간을 시간, 분, 초로 변환
         int iSec = dElapsedTime / 1000;
         int iMin = iSec / 60;
         int iHour = iMin / 60;

         iSec %= 60;
         iHour %= 60;

         swprintf_s(m_szText, L"ATTEMP : %d - SESSION 1", iAttemp);
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 80, 72, L"LitterLover2", TA_LEFT, RGB(144, 144, 144));
         swprintf_s(m_szText, L"TIME : %dH %dM %dS", iHour, iMin, iSec);
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 80, 117, L"LitterLover2", TA_LEFT, RGB(144, 144, 144));
         swprintf_s(m_szText, L"JUMPS : %d", g_iJumps);
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 80, 163, L"LitterLover2", TA_LEFT, RGB(144, 144, 144));
         swprintf_s(m_szText, L"FALLS : %d", g_iFalls);
         CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 80, 208, L"LitterLover2", TA_LEFT, RGB(144, 144, 144));
        
        //////////////////////////////저장 창 /////////////////////////
        if (CUiMgr::Get_Instance()->Get_YesOrNo() && CUiMgr::Get_Instance()->Get_Save())
        {
            HDC	hEndDC = CBmpMgr::Get_Instance()->Find_Img(L"frameEnd");
            GdiTransparentBlt(hDC, 410, 41, 220, 165, hEndDC, m_tFrame.iFrameNow * 220, m_tFrame.iMotion * 165, 220, 165, RGB(255, 255, 255));
            HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
            GdiTransparentBlt(hDC, 422, m_fYesOrNoCursorY, 22, 22, hCursor1DC, m_tFrame.iFrameNow * 11, m_tFrame.iMotion * 11, 11, 11, RGB(255, 0, 232));

            swprintf_s(m_szText, L"ARE YOU SURE?");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iAreYouSure, 68, L"LitterLover2", TA_LEFT, RGB(255, 0, 0));
            swprintf_s(m_szText, L"YES");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iNo, 112, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
            swprintf_s(m_szText, L"NO");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iYes, 155, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));

            if (CUiMgr::Get_Instance()->Get_DestroyWindow())
            {
                CObjMgr::Get_Instance()->SavePlayerPosition();
                CUiMgr::Get_Instance()->Set_DestroyWindow();
                CUiMgr::Get_Instance()->Set_YesOrNo();
                CUiMgr::Get_Instance()->Set_Save();
            }
            else if (CUiMgr::Get_Instance()->Get_BackToPrevious())
            {
                CUiMgr::Get_Instance()->Set_BackToPrevious();
                CUiMgr::Get_Instance()->Set_YesOrNo();
                CUiMgr::Get_Instance()->Set_Save();
            }
        }

        //////////////////////////////EXIT창(나가기 창)/////////////////////////
        if (CUiMgr::Get_Instance()->Get_YesOrNo() && !CUiMgr::Get_Instance()->Get_Save())
        {
            HDC	hEndDC = CBmpMgr::Get_Instance()->Find_Img(L"frameEnd");
            GdiTransparentBlt(hDC, 410, 41, 220, 165, hEndDC, m_tFrame.iFrameNow * 220, m_tFrame.iMotion * 165, 220, 165, RGB(255, 255, 255));
            HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
            GdiTransparentBlt(hDC, 422, m_fYesOrNoCursorY, 22, 22, hCursor1DC, m_tFrame.iFrameNow * 11, m_tFrame.iMotion * 11, 11, 11, RGB(255, 0, 232));

            swprintf_s(m_szText, L"ARE YOU SURE?");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iAreYouSure, 68, L"LitterLover2", TA_LEFT, RGB(255, 0, 0));
            swprintf_s(m_szText, L"YES");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iNo, 112, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
            swprintf_s(m_szText, L"NO");
            CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iYes, 155, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));


            if (CUiMgr::Get_Instance()->Get_DestroyWindow())
            {/*
                if (GetAsyncKeyState(VK_RETURN))
                {*/
                DestroyWindow(g_hWnd);
                //}
            }
            else if (CUiMgr::Get_Instance()->Get_BackToPrevious())
            {
                CUiMgr::Get_Instance()->Set_YesOrNo();
                CUiMgr::Get_Instance()->Set_BackToPrevious();
            }
        }


        ///////////////////////////인벤토리////////////////////////////////////
        if (CUiMgr::Get_Instance()->Get_Inventory())
        {
            HDC	hEndDC = CBmpMgr::Get_Instance()->Find_Img(L"Inven");
            GdiTransparentBlt(hDC, 410, 41,220, 199, hEndDC,m_tFrame.iFrameNow * 220, m_tFrame.iMotion * 199,220, 199, RGB(255, 255, 255));
            HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
            GdiTransparentBlt(hDC, 422, m_fInvenCursorY,22, 22, hCursor1DC,m_tFrame.iFrameNow * 11, m_tFrame.iMotion * 11,11, 11, RGB(255, 0, 232));
            HDC	hBack1DC = CBmpMgr::Get_Instance()->Find_Img(L"back");
            GdiTransparentBlt(hDC, m_iBack, 190, 32, 28, hBack1DC, m_tFrame.iFrameNow * 16, m_tFrame.iMotion * 14, 16, 14, RGB(255, 0, 232));

            if (CUiMgr::Get_Instance()->Get_Merchant_Crown())
            {
                swprintf_s(m_szText, L"Crown");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iCrown, 72, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
                //체크박스 
                if (CUiMgr::Get_Instance()->Get_Crown())
                {//체크박스 체크 된 박스 
                    HDC	hCheckBox1DC = CBmpMgr::Get_Instance()->Find_Img(L"checkbox2");
                    GdiTransparentBlt(hDC, m_iCrown + 75, 71, 26, 26, hCheckBox1DC, m_tFrame.iFrameNow * 13, m_tFrame.iMotion * 13, 13, 13, RGB(255, 0, 232));
                }
                else
                { //체크박스 체크 안된 박스 
                    HDC	hCheckBox1DC = CBmpMgr::Get_Instance()->Find_Img(L"checkbox1");
                    GdiTransparentBlt(hDC, m_iCrown + 75, 71, 26, 26, hCheckBox1DC, m_tFrame.iFrameNow * 13, m_tFrame.iMotion * 13, 13, 13, RGB(255, 0, 232));
                }
            }
            if (CUiMgr::Get_Instance()->Get_Merchant_KingShoes())
            {
                swprintf_s(m_szText, L"King Shoes");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iKingShoes, 113, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
                if (CUiMgr::Get_Instance()->Get_KingShoes())
                {//체크박스 체크 된 박스 
                    HDC	hCheckBox5DC = CBmpMgr::Get_Instance()->Find_Img(L"checkbox2");
                    GdiTransparentBlt(hDC, m_iKingShoes + 124, 112, 26, 26, hCheckBox5DC, m_tFrame.iFrameNow * 13, m_tFrame.iMotion * 13, 13, 13, RGB(255, 0, 232));
                }
                else
                { //체크박스 체크 안된 박스 
                    HDC	hCheckBox2DC = CBmpMgr::Get_Instance()->Find_Img(L"checkbox1");
                    GdiTransparentBlt(hDC, m_iKingShoes + 124, 112, 26, 26, hCheckBox2DC, m_tFrame.iFrameNow * 13, m_tFrame.iMotion * 13, 13, 13, RGB(255, 0, 232));
                }
            }
            if (CUiMgr::Get_Instance()->Get_Merchant_GiantBoots())
            {
                swprintf_s(m_szText, L"Giant Boots");
                CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iGaintBoots, 155, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
                if (CUiMgr::Get_Instance()->Get_GiantBoots())
                {//체크박스 체크 된 박스 
                    HDC	hCheckBox6DC = CBmpMgr::Get_Instance()->Find_Img(L"checkbox2");
                    GdiTransparentBlt(hDC, m_iGaintBoots + 135, 154, 26, 26, hCheckBox6DC, m_tFrame.iFrameNow * 13, m_tFrame.iMotion * 13, 13, 13, RGB(255, 0, 232));
                }
                else
                { //체크박스 체크 안된 박스 
                    HDC	hCheckBox3DC = CBmpMgr::Get_Instance()->Find_Img(L"checkbox1");
                    GdiTransparentBlt(hDC, m_iGaintBoots + 135, 154, 26, 26, hCheckBox3DC, m_tFrame.iFrameNow * 13, m_tFrame.iMotion * 13, 13, 13, RGB(255, 0, 232));
                }

            }
            if (CUiMgr::Get_Instance()->Get_BackToPrevious())
            {
                CUiMgr::Get_Instance()->Set_Inventory();
                CUiMgr::Get_Instance()->Set_BackToPrevious();
            }
        }

    }
}

void CUi::Release()
{
}

