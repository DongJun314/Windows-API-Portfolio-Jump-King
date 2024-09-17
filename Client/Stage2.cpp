#include "stdafx.h"
#include "Stage2.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "DropItem.h"
#include "Monster.h"
#include "SoundMgr.h"
#include "Teleport.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
    Release();
}

void CStage2::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/15.bmp", L"Second_Stage_MG1");
	
	CSoundMgr::Get_Instance()->PlayBGM(L"Nature bg.wav", g_fVolume);

}

int CStage2::Update()
{
	CObjMgr::Get_Instance()->Update();

    return 0;
}

void CStage2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage2::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

	HDC		h1StageMG1DC = CBmpMgr::Get_Instance()->Find_Img(L"Second_Stage_MG1");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, WINCX, WINCY, h1StageMG1DC, 0, 0, SRCCOPY);
	/*HDC		h1StageMG2DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG2");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY, WINCX, WINCY, h1StageMG2DC, 0, 0, SRCCOPY);
	HDC		h1StageMG3DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG3");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 2, WINCX, WINCY, h1StageMG3DC, 0, 0, SRCCOPY);
	HDC		h1StageMG4DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG4");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 3, WINCX, WINCY, h1StageMG4DC, 0, 0, SRCCOPY);*/

	CLineMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage2::Release()
{
}
