#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "UiMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CSoundMgr::Get_Instance()->Initialize();
	CBmpMgr	 ::Get_Instance()->Insert_Bmp(L"../Resource/Back.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64()) {
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwTime = GetTickCount64();
		SetWindowText(g_hWnd, m_szFPS);
	}

	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	CSceneMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	CSoundMgr::Destroy_Instance();
	CBmpMgr  ::Destroy_Instance();
	CKeyMgr  ::Destroy_Instance();
	CLineMgr ::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr	 ::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CUiMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
