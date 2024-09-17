#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "UiMgr.h"

CMyMenu::CMyMenu() : dwTime(GetTickCount64()), m_bStartMenu(false),
	 m_iNewGameX(120), m_iOtherBabeX(120), m_iOptionsX(120), m_iExtraX(120),
	m_iQuitX(120), m_iAreYouSure(205), m_iNo(205), m_iYes(205), m_bYesOrNo(false),
	m_bBackToPrevious(false), m_bDestroyWindow(false), m_iCursorIndex(0), m_iYesOrNoCursorIndex(0),
	m_fYesOrNoCursorY(325), m_bLoad(false)
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	static bool openingThemePlayed = false;

	CSoundMgr::Get_Instance()->PlayBGM(L"menu_intro.wav", g_fVolume);
	

	CBmpMgr  ::Get_Instance()->Insert_Bmp(L"../Resource/Logo/title_logo.bmp", L"title_logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/frame_StartMenu.bmp", L"frame_StartMenu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/frameEnd.bmp", L"frameEnd");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/gUI/cursor.bmp", L"cursor");
}

int CMyMenu::Update()
{
	Key_Input();

	if (!m_bYesOrNo)
	{
		if (m_iCursorIndex == 0)
		{
			m_fCursorY = 325.f;
			m_iNewGameX = 132;
		}
		else
			m_iNewGameX = 120;

		if (m_iCursorIndex == 1)
		{
			m_fCursorY = 367.f;
			m_iOtherBabeX = 132;
		}
		else
			m_iOtherBabeX = 120;

		if (m_iCursorIndex == 2)
		{
			m_fCursorY = 409.f;
			m_iOptionsX = 132;
		}
		else
			m_iOptionsX = 120;

		if (m_iCursorIndex == 3)
		{
			m_fCursorY = 451.f;
			m_iExtraX = 132;
		}
		else
			m_iExtraX = 120;

		if (m_iCursorIndex == 4)
		{
			m_fCursorY = 493.f;
			m_iQuitX = 132;
		}
		else
			m_iQuitX = 120;
	}

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyMenu::Late_Update()
{
	if (m_bYesOrNo)
	{
		if (m_iYesOrNoCursorIndex == 0)
		{
			m_fYesOrNoCursorY = 367.f;
			m_iNo = 222;
		}
		else
			m_iNo = 210;

		if (m_iYesOrNoCursorIndex == 1)
		{
			m_fYesOrNoCursorY = 409.f;
			m_iYes = 222;
		}
		else
			m_iYes = 210;
	}

	CObjMgr::Get_Instance()->Late_Update();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)&&!m_bStartMenu)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"title_hit.wav", SOUND_EFFECT, g_fVolume);
		m_bStartMenu = true;
		return;
	}
}

void CMyMenu::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
		if (!m_bYesOrNo)
		{
			m_iCursorIndex--;
			if (m_iCursorIndex <= 0)
			{
				m_iCursorIndex = 0;
			}
		}

		if (m_bYesOrNo)
		{
			m_iYesOrNoCursorIndex--;
			if (m_iYesOrNoCursorIndex <= 0)
			{
				m_iYesOrNoCursorIndex = 0;
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
		if (!m_bYesOrNo)
		{
			m_iCursorIndex++;
			if (m_iCursorIndex >= 4)
			{
				m_iCursorIndex = 4;
			}
		}

		if (m_bYesOrNo)
		{
			m_iYesOrNoCursorIndex++;
			if (m_iYesOrNoCursorIndex >= 1)
			{
				m_iYesOrNoCursorIndex = 1;
			}
		}
	}

	if (!m_bYesOrNo)
	{
		if (m_iCursorIndex == 0)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_1);
			}
		}
		else if (m_iCursorIndex == 1)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bLoad = true;
				m_bYesOrNo = true;
			}
		}
		else if (m_iCursorIndex == 2)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				//m_bYesOrNo = true;
			}
		}
		else if (m_iCursorIndex == 3)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
			}
		}
		else if (m_iCursorIndex == 4)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bYesOrNo = true;
			}
		}
	}

	if (m_bYesOrNo && !m_bLoad)
	{
		if (m_iYesOrNoCursorIndex == 0)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);

				m_bDestroyWindow = true;
			}
		}
		else if (m_iYesOrNoCursorIndex == 1)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);

				m_bBackToPrevious = true;
			}

		}
	}

	if (m_bYesOrNo && m_bLoad)
	{
		if (m_iYesOrNoCursorIndex == 0)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bDestroyWindow = true;
			}
		}
		else if (m_iYesOrNoCursorIndex == 1)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bBackToPrevious = true;
			}
		}
	}
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"title_logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	if (!m_bStartMenu)
	{
		swprintf_s(m_szText, L"PRESS SPACE");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 400, 380, L"LitterLover2", TA_CENTER, RGB(255, 255, 255));
	}
	else
	{
		//CUiMgr::Destroy_Instance();
		HDC	hEndDC = CBmpMgr::Get_Instance()->Find_Img(L"frame_StartMenu");
		GdiTransparentBlt(hDC, 90, 290, 220, 260, hEndDC, 0, 0, 220, 260, RGB(255, 255, 255));

		HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
		GdiTransparentBlt(hDC, 100, m_fCursorY, 22, 22, hCursor1DC, 0, 0, 11, 11, RGB(255, 0, 232));

		swprintf_s(m_szText, L"OBS recommended settings: Wiindow capture in OBS, use borderless in-game.");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 18, 400, 25, L"LitterLover2", TA_CENTER, RGB(255, 0, 0));
		swprintf_s(m_szText, L"Game Capture in OBS or in-game fullscreen DOES NOT WORK at the moment.");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 18, 400, 50, L"LitterLover2", TA_CENTER, RGB(255, 0, 0));
		swprintf_s(m_szText, L"ⓒ 2019 NEXILE");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 705, 75, L"LitterLover2", TA_RIGHT, RGB(144, 144, 144));
		swprintf_s(m_szText, L"ALL PROGRESS IS SAVED AUTOMATICALLY.");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, 728, 562, L"LitterLover2", TA_RIGHT, RGB(144, 144, 144));


		swprintf_s(m_szText, L"NEW GAME");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 24, m_iNewGameX, 325, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
		swprintf_s(m_szText, L"LOAD GAME");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 24, m_iOtherBabeX, 367, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
		swprintf_s(m_szText, L"OTHER BABES");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 24, m_iOptionsX, 409, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
		swprintf_s(m_szText, L"OPTIONS");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 24, m_iExtraX, 451, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
		swprintf_s(m_szText, L"QUIT");
		CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 24, m_iQuitX, 493, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));

		//////////////////////////////////////파일 불러오기//////////////////////////////////
		if (m_bYesOrNo && m_bLoad)
		{
			HDC	hEndDC = CBmpMgr::Get_Instance()->Find_Img(L"frameEnd");
			GdiTransparentBlt(hDC, 180, 290, 220, 165, hEndDC, 0, 0, 220, 165, RGB(255, 255, 255));

			HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
			GdiTransparentBlt(hDC, 190, m_fYesOrNoCursorY, 22, 22, hCursor1DC, 0, 0, 11, 11, RGB(255, 0, 232));

			swprintf_s(m_szText, L"ARE YOU SURE?");
			CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iAreYouSure, 325, L"LitterLover2", TA_LEFT, RGB(255, 0, 0));
			swprintf_s(m_szText, L"YES");
			CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iNo, 367, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
			swprintf_s(m_szText, L"NO");
			CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iYes, 409, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));

			//문제 있음
			
			if (m_bDestroyWindow)
			{
				CObjMgr::Get_Instance()->LoadPlayerPosition();
				m_bDestroyWindow = false;
				m_bYesOrNo = false;
			}
			else if (m_bBackToPrevious)
			{
				m_bBackToPrevious = false;
				m_bYesOrNo = false;
				m_bLoad = false;
			}
		}

		/////////////////////////////////나가기 QUIT/////////////////////////////////////////
		if (m_bYesOrNo && !m_bLoad)
		{
			HDC	hEndDC = CBmpMgr::Get_Instance()->Find_Img(L"frameEnd");
			GdiTransparentBlt(hDC, 180, 290, 220, 165, hEndDC, 0, 0, 220, 165, RGB(255, 255, 255));

			HDC	hCursor1DC = CBmpMgr::Get_Instance()->Find_Img(L"cursor");
			GdiTransparentBlt(hDC, 190, m_fYesOrNoCursorY, 22, 22, hCursor1DC, 0, 0, 11, 11, RGB(255, 0, 232));

			swprintf_s(m_szText, L"ARE YOU SURE?");
			CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iAreYouSure, 325, L"LitterLover2", TA_LEFT, RGB(255, 0, 0));
			swprintf_s(m_szText, L"YES");
			CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iNo, 367, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));
			swprintf_s(m_szText, L"NO");
			CUiMgr::Get_Instance()->Render_Font(hDC, m_szText, 22, m_iYes, 409, L"LitterLover2", TA_LEFT, RGB(255, 255, 255));

			if (m_bDestroyWindow)
			{
				DestroyWindow(g_hWnd);
			}
			else if (m_bBackToPrevious)
			{
				m_bBackToPrevious = false;
				m_bYesOrNo = false;
			}
		}
	}
	

	CObjMgr::Get_Instance()->Render(hDC); 
}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
}