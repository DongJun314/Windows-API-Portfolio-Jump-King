#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float* pY, float fX, float fY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Info().tLPoint.fX &&
			fX <  iter->Get_Info().tRPoint.fX)
		{
			if (fY >= next(iter)->Get_Info().tLPoint.fY &&
				fY < iter->Get_Info().tLPoint.fY)
			{
				pTarget = iter;
			}
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	x2 = pTarget->Get_Info().tRPoint.fX;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

	return true;
}

bool CLineMgr::Collision_Wall(float* pY, float fX, float fY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (fY > iter->Get_Info().tLPoint.fY &&
			fY < iter->Get_Info().tLPoint.fY)
		{
			if (iter->Get_Info().tLPoint.fX ==
				iter->Get_Info().tRPoint.fX)
			{
				if (fX + 25 >= iter->Get_Info().tLPoint.fX)
				{
					pTarget = iter;
				}
				else if (fX - 25 <= iter->Get_Info().tRPoint.fX)
				{
					pTarget = iter;
				}
				else
					return false;
			}
		}
		
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	x2 = pTarget->Get_Info().tRPoint.fX;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

	return true;
}

void CLineMgr::Initialize(void)
{
	//Load_Line();
	//1 stage 중간 네모 구조물
	m_LineList.push_back(new CLine(LINEPOINT{ 310,70 }, LINEPOINT{ 310, 145 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 310,70 }, LINEPOINT{ 490,70 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 490,70 }, LINEPOINT{ 490,145 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 310,145 }, LINEPOINT{ 490,145 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//1스테이지 바닥 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 5,0 }, LINEPOINT{ 5, 307 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5,307 }, LINEPOINT{ 208, 307 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 208,307 }, LINEPOINT{ 208, 548 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 208,548 }, LINEPOINT{ 593, 548 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 593, 548 }, LINEPOINT{ 593, 307 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 593, 307 }, LINEPOINT{ 794, 307 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, 307 }, LINEPOINT{ 794, 0 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//2스테이지 왼쪽 세로 줄 네모포함
	m_LineList.push_back(new CLine(LINEPOINT{ 5,0 }, LINEPOINT{ 5, -323 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -323 }, LINEPOINT{ 132,-323 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 132,-323 }, LINEPOINT{ 132,-464 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 132,-464 }, LINEPOINT{ 5,-464 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5,-464 }, LINEPOINT{ 5,-600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//2스테이지 왼쪽 첫번째 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 319, -425 }, LINEPOINT{ 200, -425 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 200, -323 }, LINEPOINT{ 319, -323 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 319, -323 }, LINEPOINT{ 319, -425 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 200, -323 }, LINEPOINT{ 200, -425 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//2스테이지 오른쪽 맨 밑에 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 495, -105 }, LINEPOINT{ 652, -105 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 652, -105 }, LINEPOINT{ 652, -53 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 495, -105 }, LINEPOINT{ 495, -53 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 495, -53 }, LINEPOINT{ 652, -53 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//2스테이지 오른쪽 두번째 위 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 428, -265 }, LINEPOINT{ 546, -265 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 428, -265 }, LINEPOINT{ 428, -215 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 546, -265 }, LINEPOINT{ 546, -215 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 546, -215 }, LINEPOINT{ 428, -215 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//오른쪽 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 794, 0 }, LINEPOINT{ 794, -215 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -215 }, LINEPOINT{ 682, -215 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 682, -215 }, LINEPOINT{ 682, -265 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 682, -265 }, LINEPOINT{ 794, -265 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -265 }, LINEPOINT{ 794, -600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));


	//3스테이지 왼쪽 세로 라인 네모 포함
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -600 }, LINEPOINT{ 5, -1016 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -1016 }, LINEPOINT{ 104, -1016 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 104, -1016 }, LINEPOINT{ 104, -1038 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 104, -1038 }, LINEPOINT{ 5, -1038 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -1038 }, LINEPOINT{ 5, -1200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//3스테이지 오른쪽 밑에 제일 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 349, -692 }, LINEPOINT{ 425, -692 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 349, -692 }, LINEPOINT{ 349, -668 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 349, -668 }, LINEPOINT{ 425, -668 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 425, -692 }, LINEPOINT{ 425, -668 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//3스테이지 오른쪽 밑에 왼쪽에서 두번째 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 535, -692 }, LINEPOINT{ 625, -692 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 625, -692 }, LINEPOINT{ 625, -668 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 535, -668 }, LINEPOINT{ 625, -668 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 535, -668 }, LINEPOINT{ 535, -692 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//3스테이지 오른쪽 세로 라인 네모 포함											 
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -600 }, LINEPOINT{ 794, -750 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -750 }, LINEPOINT{ 708, -750 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 708, -750 }, LINEPOINT{ 708, -771 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 708, -771 }, LINEPOINT{ 794, -771 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -771 }, LINEPOINT{ 794, -1200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//3스테이지 가운데 큰 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 321, -775 }, LINEPOINT{ 559, -775 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 321, -775 }, LINEPOINT{ 321, -825 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 321, -825 }, LINEPOINT{ 481, -825 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 481, -825 }, LINEPOINT{ 481, -853 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 481, -853 }, LINEPOINT{ 559, -853 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 559, -853 }, LINEPOINT{ 559, -775 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//3스테이지 가운데 왼쪽위 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 267, -923 }, LINEPOINT{ 359, -923 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 267, -923 }, LINEPOINT{ 267, -999 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 267, -999 }, LINEPOINT{ 359, -999 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 359, -999 }, LINEPOINT{ 359, -923 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//3스테이지 맨위 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 230, -1200 }, LINEPOINT{ 230, -1175 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 230, -1175 }, LINEPOINT{ 344, -1175 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 344, -1175 }, LINEPOINT{ 344, -1200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));


	//4스테이지 왼쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -1200 }, LINEPOINT{ 5, -1416 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -1416 }, LINEPOINT{ 104, -1416 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 104, -1416 }, LINEPOINT{ 104, -1438 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 104, -1438 }, LINEPOINT{ 5, -1438 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -1438 }, LINEPOINT{ 5, -1800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//4스테이지 중간 네모 아래 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 227, -1200 }, LINEPOINT{ 227, -1266 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 227, -1266 }, LINEPOINT{ 345, -1266 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 345, -1266 }, LINEPOINT{ 345, -1200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//4스테이지 중간 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 228, -1415 }, LINEPOINT{ 228, -1439 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 228, -1439 }, LINEPOINT{ 345, -1439 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 345, -1439 }, LINEPOINT{ 345, -1415 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 345, -1415 }, LINEPOINT{ 228, -1415 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//4스테이지 가운데 큰 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 228, -1522 }, LINEPOINT{ 292, -1522 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 292, -1522 }, LINEPOINT{ 292, -1652 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 292, -1652 }, LINEPOINT{ 251, -1652 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 251, -1652 }, LINEPOINT{ 251, -1800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 228, -1522 }, LINEPOINT{ 228, -1800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//4스테이지 가운데 제일 큰 8각형
	m_LineList.push_back(new CLine(LINEPOINT{ 494, -1415 }, LINEPOINT{ 575, -1415 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 494, -1415 }, LINEPOINT{ 494, -1532 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 494, -1532 }, LINEPOINT{ 548, -1532 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 548, -1532 }, LINEPOINT{ 548, -1680 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 548, -1680 }, LINEPOINT{ 665, -1680 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 665, -1680 }, LINEPOINT{ 665, -1654 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 665, -1654 }, LINEPOINT{ 574, -1654 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 574, -1654 }, LINEPOINT{ 574, -1415 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//4스테이지 맨위 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 547, -1800 }, LINEPOINT{ 547, -1775 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 547, -1775 }, LINEPOINT{ 576, -1775 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 576, -1775 }, LINEPOINT{ 576, -1800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));


	//4스테이지 오른쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -1200 }, LINEPOINT{ 794, -1560 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -1560 }, LINEPOINT{ 720, -1560 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 720, -1560 }, LINEPOINT{ 720, -1587 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 720, -1587 }, LINEPOINT{ 794, -1587 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -1587 }, LINEPOINT{ 794, -1800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//5스테이지 왼쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -1800 }, LINEPOINT{ 5, -1976 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -1976 }, LINEPOINT{ 65, -1976 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 65, -1976 }, LINEPOINT{ 65, -2000 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 65, -2000 }, LINEPOINT{ 5, -2000 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -2000 }, LINEPOINT{ 5, -2400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_WALL)));

	//5스테이지 오른쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -1800 }, LINEPOINT{ 794, -2109 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -2109 }, LINEPOINT{ 735, -2109 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 735, -2109 }, LINEPOINT{ 735, -2132 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 735, -2132 }, LINEPOINT{ 794, -2132 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -2132 }, LINEPOINT{ 794, -2400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//5스테이지 왼쪽 아래 5각형
	m_LineList.push_back(new CLine(LINEPOINT{ 228, -1800 }, LINEPOINT{ 228, -1855 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 228, -1855 }, LINEPOINT{ 188, -1855 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 188, -1855 }, LINEPOINT{ 188, -1880 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 188, -1880 }, LINEPOINT{ 251, -1880 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 251, -1880 }, LINEPOINT{ 251, -1800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//5스테이지 오른쪽 아래 5각형
	m_LineList.push_back(new CLine(LINEPOINT{ 547, -1800 }, LINEPOINT{ 547, -1879 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 547, -1879 }, LINEPOINT{ 612, -1879 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 612, -1879 }, LINEPOINT{ 612, -1852 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 612, -1852 }, LINEPOINT{ 576, -1852 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 576, -1852 }, LINEPOINT{ 576, -1800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//5스테이지 아래 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 549, -1975 }, LINEPOINT{ 610, -1975 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 610, -1975 }, LINEPOINT{ 610, -1999 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 610, -1999 }, LINEPOINT{ 549, -1999 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 549, -1999 }, LINEPOINT{ 549, -1975 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//5스테이지 왼쪽에서 네번째 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 375, -2256 }, LINEPOINT{ 424, -2256 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 424, -2256 }, LINEPOINT{ 424, -2279 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 424, -2279 }, LINEPOINT{ 375, -2279 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 375, -2279 }, LINEPOINT{ 375, -2256 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//5스테이지 왼쪽에서 세번째 네모													
	m_LineList.push_back(new CLine(LINEPOINT{ 482, -2230 }, LINEPOINT{ 531, -2230 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 531, -2230 }, LINEPOINT{ 531, -2252 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 531, -2252 }, LINEPOINT{ 482, -2252 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 482, -2252 }, LINEPOINT{ 482, -2230 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//5스테이지 왼쪽에서 두번째 네모													
	m_LineList.push_back(new CLine(LINEPOINT{ 318, -2282 }, LINEPOINT{ 318, -2306 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 318, -2306 }, LINEPOINT{ 269, -2306 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 269, -2306 }, LINEPOINT{ 269, -2282 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 269, -2282 }, LINEPOINT{ 318, -2282 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//5스테이지 제일 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 68, -2230 }, LINEPOINT{ 117, -2230 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 117, -2230 }, LINEPOINT{ 117, -2252 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 117, -2252 }, LINEPOINT{ 68, -2252 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 68, -2252 }, LINEPOINT{ 68, -2230 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//5스테이지 맨위 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -2401 }, LINEPOINT{ 255, -2401 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 255, -2400 }, LINEPOINT{ 255, -2376 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 255, -2376 }, LINEPOINT{ 545, -2376 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 545, -2376 }, LINEPOINT{ 545, -2400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 545, -2400 }, LINEPOINT{ 794, -2400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//6스테이지 왼쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -2410 }, LINEPOINT{ 794, -2410 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 265, -2400 }, LINEPOINT{ 265, -2452 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 265, -2452 }, LINEPOINT{ 5, -2452 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -2452 }, LINEPOINT{ 5, -2615 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -2615 }, LINEPOINT{ 265, -2615 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 265, -2615 }, LINEPOINT{ 265, -2627 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 265, -2627 }, LINEPOINT{ 144, -2748 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 144, -2748 }, LINEPOINT{ 144, -2816 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 144, -2816 }, LINEPOINT{ 94, -2866 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 94, -2866 }, LINEPOINT{ 5, -2866 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -2866 }, LINEPOINT{ 5, -2960 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -2960 }, LINEPOINT{ 45, -3000 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_DIAGONAL)));

	//6스테이지 오른쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -2400 }, LINEPOINT{ 794, -2576 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -2576 }, LINEPOINT{ 643, -2576 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 643, -2576 }, LINEPOINT{ 643, -2604 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 643, -2604 }, LINEPOINT{ 562, -2604 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 562, -2604 }, LINEPOINT{ 562, -2626 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 562, -2626 }, LINEPOINT{ 643, -2626 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 643, -2626 }, LINEPOINT{ 643, -2675 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 643, -2675 }, LINEPOINT{ 637, -2675 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 637, -2675 }, LINEPOINT{ 637, -2678 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 637, -2678 }, LINEPOINT{ 680, -2720 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 680, -2720 }, LINEPOINT{ 794, -2720 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -2720 }, LINEPOINT{ 794, -2857 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -2857 }, LINEPOINT{ 682, -2857 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 682, -2857 }, LINEPOINT{ 682, -2868 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 682, -2868 }, LINEPOINT{ 788, -2976 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 788, -2976 }, LINEPOINT{ 794, -2976 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -2976 }, LINEPOINT{ 794, -3600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//6스테이지 중간 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 282, -2776 }, LINEPOINT{ 425, -2776 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 282, -2776 }, LINEPOINT{ 282, -2856 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 282, -2856 }, LINEPOINT{ 319, -2893 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 319, -2893 }, LINEPOINT{ 319, -2867 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 319, -2867 }, LINEPOINT{ 387, -2867 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -2867 }, LINEPOINT{ 387, -2893 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -2893 }, LINEPOINT{ 425, -2856 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 425, -2856 }, LINEPOINT{ 425, -2776 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//7스테이지 왼쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 45, -3000 }, LINEPOINT{ 102, -3057 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 102, -3057 }, LINEPOINT{ 102, -3078 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 102, -3078 }, LINEPOINT{ 5, -3078 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -3078 }, LINEPOINT{ 5, -3310 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -3310 }, LINEPOINT{ 130, -3310 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 130, -3310 }, LINEPOINT{ 130, -3424 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 130, -3424 }, LINEPOINT{ 134, -3424 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 134, -3424 }, LINEPOINT{ 134, -3427 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 134, -3427 }, LINEPOINT{ 94, -3466 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 94, -3466 }, LINEPOINT{ 5, -3466 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -3466 }, LINEPOINT{ 5, -3552 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -3552 }, LINEPOINT{ 82, -3552 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 82, -3552 }, LINEPOINT{ 82, -3557 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 82, -3557 }, LINEPOINT{ 40, -3600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_DIAGONAL)));

	//7스테이지 오른쪽 밑에 맨 왼쪽 6각형
	m_LineList.push_back(new CLine(LINEPOINT{ 375, -3122 }, LINEPOINT{ 429, -3122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 429, -3122 }, LINEPOINT{ 429, -3056 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 429, -3056 }, LINEPOINT{ 465, -3056 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 465, -3056 }, LINEPOINT{ 465, -3146 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 465, -3146 }, LINEPOINT{ 375, -3146 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 375, -3146 }, LINEPOINT{ 375, -3122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//7스테이지 오른쪽 밑에 맨 왼쪽 두번째 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 548, -3056 }, LINEPOINT{ 586, -3056 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 586, -3056 }, LINEPOINT{ 586, -3146 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 586, -3146 }, LINEPOINT{ 548, -3146 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 548, -3146 }, LINEPOINT{ 548, -3056 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//7스테이지 오른쪽 밑에 맨 왼쪽 세번째 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 669, -3056 }, LINEPOINT{ 706, -3056 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 706, -3056 }, LINEPOINT{ 706, -3120 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 706, -3120 }, LINEPOINT{ 669, -3120 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 669, -3120 }, LINEPOINT{ 669, -3056 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//7스테이지 오른쪽 밑에 맨 왼쪽 세번째 위에 네모								 
	m_LineList.push_back(new CLine(LINEPOINT{ 655, -3306 }, LINEPOINT{ 705, -3306 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 705, -3306 }, LINEPOINT{ 705, -3254 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 705, -3254 }, LINEPOINT{ 655, -3254 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 655, -3254 }, LINEPOINT{ 655, -3306 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//7스테이지 오른쪽 밑에 맨 왼쪽 세번째 위에 네모								   
	m_LineList.push_back(new CLine(LINEPOINT{ 667, -3600 }, LINEPOINT{ 667, -3574 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 667, -3574 }, LINEPOINT{ 719, -3574 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 719, -3574 }, LINEPOINT{ 719, -3600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//7스테이지 중간 이상한 도형													
	m_LineList.push_back(new CLine(LINEPOINT{ 429, -3215 }, LINEPOINT{ 465, -3215 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 465, -3215 }, LINEPOINT{ 465, -3416 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 465, -3416 }, LINEPOINT{ 518, -3416 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 518, -3416 }, LINEPOINT{ 518, -3440 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 518, -3440 }, LINEPOINT{ 387, -3440 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -3440 }, LINEPOINT{ 387, -3416 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -3416 }, LINEPOINT{ 429, -3416 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 429, -3416 }, LINEPOINT{ 429, -3346 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 429, -3346 }, LINEPOINT{ 306, -3346 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 306, -3346 }, LINEPOINT{ 306, -3322 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 306, -3322 }, LINEPOINT{ 429, -3322 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 429, -3322 }, LINEPOINT{ 429, -3215 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//8스테이지 왼쪽 세로
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -3600 }, LINEPOINT{ 78, -3600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 78, -3600 }, LINEPOINT{ 78, -3653 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 78, -3653 }, LINEPOINT{ 5, -3653 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -3653 }, LINEPOINT{ 5, -4015 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -4015 }, LINEPOINT{ 332, -4015 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 332, -4015 }, LINEPOINT{ 332, -4042 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 332, -4042 }, LINEPOINT{ 25, -4042 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 25, -4042 }, LINEPOINT{ 25, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 25, -4122 }, LINEPOINT{ 64, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 64, -4122 }, LINEPOINT{ 64, -4200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//8스테이지 오른쪽 세로
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -3600 }, LINEPOINT{ 794, -4015 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4015 }, LINEPOINT{ 466, -4015 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 466, -4015 }, LINEPOINT{ 466, -4040 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 466, -4040 }, LINEPOINT{ 774, -4040 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 774, -4040 }, LINEPOINT{ 774, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 774, -4122 }, LINEPOINT{ 735, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 735, -4122 }, LINEPOINT{ 735, -4200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//8스테이지 중간 이빨 모양 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 122, -4200 }, LINEPOINT{ 122, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 122, -4122 }, LINEPOINT{ 159, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 159, -4122 }, LINEPOINT{ 159, -4175 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 159, -4175 }, LINEPOINT{ 640, -4175 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 640, -4175 }, LINEPOINT{ 640, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 640, -4122 }, LINEPOINT{ 677, -4122 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 677, -4122 }, LINEPOINT{ 677, -4200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//8스테이지 중간 제일 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 241, -3776 }, LINEPOINT{ 332, -3776 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 332, -3776 }, LINEPOINT{ 332, -3800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 332, -3800 }, LINEPOINT{ 241, -3800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 241, -3800 }, LINEPOINT{ 241, -3776 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//8스테이지 중간 왼쪽에서 두번쨰 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 440, -3868 }, LINEPOINT{ 506, -3868 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 506, -3868 }, LINEPOINT{ 506, -3893 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 506, -3893 }, LINEPOINT{ 440, -3893 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 440, -3893 }, LINEPOINT{ 440, -3868 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//8스테이지 중간 왼쪽에서 세번쨰 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 494, -3655 }, LINEPOINT{ 612, -3655 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 612, -3655 }, LINEPOINT{ 612, -3679 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 612, -3679 }, LINEPOINT{ 494, -3679 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 494, -3679 }, LINEPOINT{ 494, -3655 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//9스테이지 왼쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 64, -4200 }, LINEPOINT{ 64, -4216 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 64, -4216 }, LINEPOINT{ 5, -4216 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -4216 }, LINEPOINT{ 5, -4800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//9스테이지 중간 십자가 선
	m_LineList.push_back(new CLine(LINEPOINT{ 120, -4200 }, LINEPOINT{ 120, -4216 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 120, -4216 }, LINEPOINT{ 188, -4216 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 188, -4216 }, LINEPOINT{ 188, -4324 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 188, -4324 }, LINEPOINT{ 304, -4440 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 304, -4440 }, LINEPOINT{ 374, -4440 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 374, -4440 }, LINEPOINT{ 374, -4561 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 374, -4561 }, LINEPOINT{ 321, -4561 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 321, -4561 }, LINEPOINT{ 321, -4614 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 321, -4614 }, LINEPOINT{ 374, -4614 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 374, -4614 }, LINEPOINT{ 374, -4666 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 374, -4666 }, LINEPOINT{ 425, -4666 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 425, -4666 }, LINEPOINT{ 425, -4614 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 425, -4614 }, LINEPOINT{ 478, -4614 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 478, -4614 }, LINEPOINT{ 478, -4561 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 478, -4561 }, LINEPOINT{ 425, -4561 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 425, -4561 }, LINEPOINT{ 425, -4440 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 425, -4440 }, LINEPOINT{ 495, -4440 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 495, -4440 }, LINEPOINT{ 611, -4324 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 611, -4324 }, LINEPOINT{ 611, -4228 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 611, -4228 }, LINEPOINT{ 638, -4228 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 638, -4228 }, LINEPOINT{ 638, -4218 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 638, -4218 }, LINEPOINT{ 679, -4218 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 679, -4218 }, LINEPOINT{ 679, -4200 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//9스테이지 오른쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 736, -4200 }, LINEPOINT{ 736, -4218 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 736, -4218 }, LINEPOINT{ 794, -4218 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4218 }, LINEPOINT{ 794, -4335 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4335 }, LINEPOINT{ 747, -4335 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 747, -4335 }, LINEPOINT{ 747, -4386 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 747, -4386 }, LINEPOINT{ 794, -4386 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4386 }, LINEPOINT{ 794, -4496 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4496 }, LINEPOINT{ 747, -4496 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 747, -4496 }, LINEPOINT{ 747, -4547 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 747, -4547 }, LINEPOINT{ 794, -4547 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4547 }, LINEPOINT{ 794, -4775 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4775 }, LINEPOINT{ 694, -4775 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 694, -4775 }, LINEPOINT{ 694, -4800 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//10스테이지 중간 맨 아래 빙판
	m_LineList.push_back(new CLine(LINEPOINT{ 346, -4774 }, LINEPOINT{ 520, -4948 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 346, -4774 }, LINEPOINT{ 305, -4814 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 520, -4948 }, LINEPOINT{ 520, -4961 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 520, -4961 }, LINEPOINT{ 438, -4961 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 438, -4961 }, LINEPOINT{ 438, -4948 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 438, -4948 }, LINEPOINT{ 305, -4814 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_DIAGONAL)));

	//10스테이지 왼쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -4335 }, LINEPOINT{ 5, -4963 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -4963 }, LINEPOINT{ 105, -4963 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 105, -4963 }, LINEPOINT{ 160, -4908 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 160, -4908 }, LINEPOINT{ 200, -4948 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 200, -4948 }, LINEPOINT{ 81, -5067 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 81, -5067 }, LINEPOINT{ 5, -5067 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -5067 }, LINEPOINT{ 5, -5400 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));

	//10스테이지 오른쪽 세로 라인
	m_LineList.push_back(new CLine(LINEPOINT{ 694, -4800 }, LINEPOINT{ 694, -4854 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 694, -4854 }, LINEPOINT{ 794, -4854 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -4854 }, LINEPOINT{ 794, -5148 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -5148 }, LINEPOINT{ 748, -5148 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 748, -5148 }, LINEPOINT{ 706, -5106 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 706, -5106 }, LINEPOINT{ 665, -5147 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 665, -5147 }, LINEPOINT{ 734, -5214 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 734, -5214 }, LINEPOINT{ 734, -5400 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));

	//10스테이지 중간 왼쪽 6각형
	m_LineList.push_back(new CLine(LINEPOINT{ 240, -5240 }, LINEPOINT{ 319, -5240 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 319, -5240 }, LINEPOINT{ 319, -5200 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 319, -5200 }, LINEPOINT{ 306, -5200 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 306, -5200 }, LINEPOINT{ 306, -5135 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 306, -5135 }, LINEPOINT{ 253, -5135 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 253, -5135 }, LINEPOINT{ 253, -5200 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 253, -5200 }, LINEPOINT{ 240, -5200 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 240, -5200 }, LINEPOINT{ 240, -5240 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));

	//10스테이지 중간 오른쪽 6각형
	m_LineList.push_back(new CLine(LINEPOINT{ 440, -5227 }, LINEPOINT{ 519, -5227 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 519, -5227 }, LINEPOINT{ 519, -5188 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 519, -5188 }, LINEPOINT{ 505, -5188 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 505, -5188 }, LINEPOINT{ 505, -5121 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 505, -5121 }, LINEPOINT{ 453, -5121 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 453, -5121 }, LINEPOINT{ 453, -5188 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 453, -5188 }, LINEPOINT{ 440, -5188 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 440, -5188 }, LINEPOINT{ 440, -5227 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));

	//10스테이지 민테 중간 6각형
	m_LineList.push_back(new CLine(LINEPOINT{ 200, -4948 }, LINEPOINT{ 280, -4948 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 280, -4948 }, LINEPOINT{ 280, -4908 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 280, -4908 }, LINEPOINT{ 265, -4908 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 265, -4908 }, LINEPOINT{ 265, -4882 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 265, -4882 }, LINEPOINT{ 214, -4882 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 214, -4882 }, LINEPOINT{ 214, -4908 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 214, -4908 }, LINEPOINT{ 200, -4908 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 200, -4908 }, LINEPOINT{ 200, -4948 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));

	//10스테이지 맨위에 오른쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 254, -5400 }, LINEPOINT{ 254, -5374 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 254, -5374 }, LINEPOINT{ 306, -5374 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 306, -5374 }, LINEPOINT{ 306, -5400 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 306, -5400 }, LINEPOINT{ 254, -5400 }, LINE_TYPE(LT_ICE), LINE_SHAPE(LS_GROUND)));



	//11스테이지 맨아래 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 148, -5426 }, LINEPOINT{ 224, -5426 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 148, -5426 }, LINEPOINT{ 148, -5400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 224, -5426 }, LINEPOINT{ 224, -5400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 224, -5400 }, LINEPOINT{ 148, -5400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//10스테이지 맨위에 가운데 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -5482 }, LINEPOINT{ 439, -5482 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 439, -5482 }, LINEPOINT{ 439, -5507 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 439, -5507 }, LINEPOINT{ 387, -5507 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -5507 }, LINEPOINT{ 387, -5482 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));


	//10스테이지 맨위에 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -5642 }, LINEPOINT{ 399, -5642 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 399, -5642 }, LINEPOINT{ 399, -5706 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 399, -5706 }, LINEPOINT{ 387, -5706 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 387, -5706 }, LINEPOINT{ 387, -5642 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));


	//10스테이지 맨위에 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 267, -5708 }, LINEPOINT{ 318, -5708 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 318, -5708 }, LINEPOINT{ 318, -5734 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 318, -5734 }, LINEPOINT{ 267, -5734 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 267, -5734 }, LINEPOINT{ 267, -5708 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));


	//10스테이지 맨위에 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 560, -5400 }, LINEPOINT{ 560, -5600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 560, -5600 }, LINEPOINT{ 613, -5600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 613, -5600 }, LINEPOINT{ 613, -5400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 613, -5400 }, LINEPOINT{ 560, -5400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));

	//10스테이지 맨위에 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 560, -5722 }, LINEPOINT{ 613, -5722 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 613, -5722 }, LINEPOINT{ 613, -5841 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 613, -5841 }, LINEPOINT{ 560, -5841 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 560, -5841 }, LINEPOINT{ 560, -5722 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//10스테이지 맨위에 오른쪽 세로 천장 왼쪽 세로
	m_LineList.push_back(new CLine(LINEPOINT{ 734, -5400 }, LINEPOINT{ 794, -5500 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_DIAGONAL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -5500 }, LINEPOINT{ 794, -6600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 794, -6600 }, LINEPOINT{ 5, -6600 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 5, -6600 }, LINEPOINT{ 5, -5400 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));

	//10스테이지 맨위에 오른쪽 세로 천장 왼쪽 세로
	m_LineList.push_back(new CLine(LINEPOINT{ 187, -5935 }, LINEPOINT{ 238, -5935 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 238, -5935 }, LINEPOINT{ 238, -5975 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 238, -5975 }, LINEPOINT{ 279, -5975 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 279, -5975 }, LINEPOINT{ 279, -6027 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 279, -6027 }, LINEPOINT{ 187, -6027 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 187, -6027 }, LINEPOINT{ 187, -5935 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	//10스테이지 왼쪽 아래 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 80, -6028 }, LINEPOINT{ 105, -6028 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 105, -6028 }, LINEPOINT{ 105, -6053 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 105, -6053 }, LINEPOINT{ 80, -6053 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 80, -6053 }, LINEPOINT{ 80, -6028 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));


	//10스테이지 윗쪽 아래 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 81, -6268 }, LINEPOINT{ 105, -6268 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 105, -6268 }, LINEPOINT{ 105, -6293 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 105, -6293 }, LINEPOINT{ 81, -6293 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 81, -6293 }, LINEPOINT{ 81, -6268 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));

	////10스테이지 맨위에 왼쪽 네모
	m_LineList.push_back(new CLine(LINEPOINT{ 560, -5974 }, LINEPOINT{ 613, -5974 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 560, -5974 }, LINEPOINT{ 560, -6162 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 613, -5974 }, LINEPOINT{ 613, -6347 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 613, -6347 }, LINEPOINT{ 719, -6347 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));
	m_LineList.push_back(new CLine(LINEPOINT{ 719, -6347 }, LINEPOINT{ 719, -6387 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_LEFT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 719, -6387 }, LINEPOINT{ 707, -6387 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 707, -6387 }, LINEPOINT{ 707, -6360 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 707, -6360 }, LINEPOINT{ 188, -6360 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_GROUND)));
	m_LineList.push_back(new CLine(LINEPOINT{ 188, -6360 }, LINEPOINT{ 188, -6162 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_RIGHT_WALL)));
	m_LineList.push_back(new CLine(LINEPOINT{ 188, -6162 }, LINEPOINT{ 560, -6162 }, LINE_TYPE(LT_NORMAL), LINE_SHAPE(LS_CEILING)));




}

void CLineMgr::Update(void)
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

void CLineMgr::Save_Line(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Line.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Save 완료"), L"성공", MB_OK);
}

void CLineMgr::Load_Line(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
