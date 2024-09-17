#include "stdafx.h"
#include "Stage1.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "UiMgr.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	//배경화면
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/1.bmp", L"First_Stage_MG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/2.bmp", L"First_Stage_MG2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/3.bmp", L"First_Stage_MG3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/4.bmp", L"First_Stage_MG4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/5.bmp", L"First_Stage_MG5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/15.bmp", L"Second_Stage_MG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/16.bmp", L"Second_Stage_MG2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/32.bmp", L"Third_Stage_MG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/36.bmp", L"Fourth_Stage_MG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/37.bmp", L"Fourth_Stage_MG2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/42.bmp", L"End_Stage_MG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MG/43.bmp", L"End_Stage_MG2");
	 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg1.bmp", L"First_Stage_FG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg2.bmp", L"First_Stage_FG2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg3.bmp", L"First_Stage_FG3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg4.bmp", L"First_Stage_FG4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg5.bmp", L"First_Stage_FG5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg15.bmp", L"Second_Stage_FG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg16.bmp", L"Second_Stage_FG2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg32.bmp", L"Third_Stage_FG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg36.bmp", L"Fourth_Stage_FG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg37.bmp", L"Fourth_Stage_FG2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg42.bmp", L"End_Stage_FG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/FG/fg43.bmp", L"End_Stage_FG2");


	//UI
	CUiMgr::Get_Instance()->Initialize();

	//객체 생성
	CObjMgr::Get_Instance()->Initialize();
	

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"Nature bg.wav", g_fVolume);

	//Map
	CLineMgr::Get_Instance()->Initialize();
	
}

int CStage1::Update()
{
	CObjMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
	return 0;
}

void CStage1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CUiMgr::Get_Instance()->Late_Update();
}

void CStage1::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

	//1스테이지


	//HDC		h1StageMG1DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG1");
	//// HDC에서 현재 선택된 HBITMAP을 얻어옵니다.
	//HBITMAP hBitmap = (HBITMAP)GetCurrentObject(h1StageMG1DC, OBJ_BITMAP);

	//GetRotatedBitmap(hDC, m_hBitmap, 1, RGB(255, 255, 0));

	////// 비틀린 변환을 위한 포인트 배열을 설정합니다.
	//POINT points[3];
	//points[0].x = (int)fScrollX;
	//points[0].y = (int)fScrollY;
	//points[1].x = points[0].x + WINCX;
	//points[1].y = points[0].y;
	//points[2].x = points[0].x;
	//points[2].y = points[0].y - WINCY; // 위 아래 반전을 위해 y 좌표를 음수로 설정합니다.

	//// PlgBlt 함수를 사용하여 이미지를 비틀어서 그립니다.
	//PlgBlt(hDC, points, h1StageMG1DC, 0, 0, WINCX, WINCY, nullptr, 0, 0);

	HDC		h1StageMG1DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG1");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, WINCX, WINCY, h1StageMG1DC, 0, 0, SRCCOPY);
	HDC		h1StageMG2DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG2");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY, WINCX, WINCY, h1StageMG2DC, 0, 0, SRCCOPY);
	HDC		h1StageMG3DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG3");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 2, WINCX, WINCY, h1StageMG3DC, 0, 0, SRCCOPY);
	HDC		h1StageMG4DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG4");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 3, WINCX, WINCY, h1StageMG4DC, 0, 0, SRCCOPY);
	HDC		h1StageMG5DC = CBmpMgr::Get_Instance()->Find_Img(L"First_Stage_MG5");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 4, WINCX, WINCY, h1StageMG5DC, 0, 0, SRCCOPY);

	//2스테이지
	HDC		h2StageMG1DC = CBmpMgr::Get_Instance()->Find_Img(L"Second_Stage_MG1");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 5, WINCX, WINCY, h2StageMG1DC, 0, 0, SRCCOPY);
	HDC		h2StageMG2DC = CBmpMgr::Get_Instance()->Find_Img(L"Second_Stage_MG2");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 6, WINCX, WINCY, h2StageMG2DC, 0, 0, SRCCOPY);

	//3스테이지
	HDC		h3StageMG3DC = CBmpMgr::Get_Instance()->Find_Img(L"Third_Stage_MG1");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 7, WINCX, WINCY, h3StageMG3DC, 0, 0, SRCCOPY);

	//4스테이지
	HDC		h4StageMG1DC = CBmpMgr::Get_Instance()->Find_Img(L"Fourth_Stage_MG1");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 8, WINCX, WINCY, h4StageMG1DC, 0, 0, SRCCOPY);
	HDC		h4StageMG2DC = CBmpMgr::Get_Instance()->Find_Img(L"Fourth_Stage_MG2");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 9, WINCX, WINCY, h4StageMG2DC, 0, 0, SRCCOPY);

	//5스테이지
	HDC		h5StageMG3DC = CBmpMgr::Get_Instance()->Find_Img(L"End_Stage_MG1");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 10, WINCX, WINCY, h5StageMG3DC, 0, 0, SRCCOPY);
	HDC		h5StageMG4DC = CBmpMgr::Get_Instance()->Find_Img(L"End_Stage_MG2");
	BitBlt(hDC, (int)fScrollX, (int)fScrollY - WINCY * 11, WINCX, WINCY, h5StageMG4DC, 0, 0, SRCCOPY);

	CLineMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

}

void CStage1::Release()
{
}

HBITMAP CStage1::GetRotatedBitmap(HDC hdc, HBITMAP hBitmap, float radians, COLORREF clrBack)
{
	// Create a memory DC compatible with the display 
	HDC sourceDC, destDC;
	BITMAP bm;
	HBITMAP hbmResult;
	HBITMAP hbmOldSource;
	HBITMAP hbmOldDest;
	HBRUSH hbrBack;
	HBRUSH hbrOld;
	XFORM xform;
	float cosine, sine;
	int x1, y1, x2, y2, x3, y3, minx, miny, maxx, maxy, w, h;

	sourceDC = CreateCompatibleDC(hdc);
	destDC = CreateCompatibleDC(hdc);

	// Get logical coordinates 
	GetObject(hBitmap, sizeof(bm), &bm);
	cosine = cos(radians);
	sine = sin(radians);

	//회전된 이미지의 영역을 구한다.
	// Compute dimensions of the resulting bitmap 
	// First get the coordinates of the 3 corners other than origin 
	x1 = (int)(bm.bmHeight * sine);
	y1 = (int)(bm.bmHeight * cosine);
	x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
	y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);
	x3 = (int)(bm.bmWidth * cosine);
	y3 = (int)(-bm.bmWidth * sine);
	minx = min(0, min(x1, min(x2, x3)));
	miny = min(0, min(y1, min(y2, y3)));
	maxx = max(0, max(x1, max(x2, x3)));
	maxy = max(0, max(y1, max(y2, y3)));
	w = maxx - minx;
	h = maxy - miny;

	// Create a bitmap to hold the result 
	hbmResult = CreateCompatibleBitmap(hdc, w, h);
	hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);
	hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);

	// Draw the background color before we change mapping mode 
	hbrBack = CreateSolidBrush(clrBack);
	hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);
	PatBlt(destDC, 0, 0, w, h, PATCOPY);
	DeleteObject(SelectObject(destDC, hbrOld));

	// We will use world transform to rotate the bitmap 
	SetGraphicsMode(destDC, GM_ADVANCED);
	xform.eM11 = cosine;
	xform.eM12 = -sine;
	xform.eM21 = sine;
	xform.eM22 = cosine;
	xform.eDx = (float)-minx;
	xform.eDy = (float)-miny;
	SetWorldTransform(destDC, &xform);

	// Now do the actual rotating - a pixel at a time 
	BitBlt(destDC, 0, 0, bm.bmWidth, bm.bmHeight, sourceDC, 0, 0, SRCCOPY);

	// Restore DCs 
	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);
	DeleteDC(sourceDC);
	DeleteDC(destDC);

	return hbmResult;
}
