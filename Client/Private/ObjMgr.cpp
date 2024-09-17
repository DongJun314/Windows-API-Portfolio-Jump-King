#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Monster.h"
#include "DropItem.h"
#include "Teleport.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJ_ID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*   pTarget   = nullptr;
	float	fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth	  = iter->Get_Info().fX - pObj->Get_Info().fX;
		float	fHeight   = iter->Get_Info().fY - pObj->Get_Info().fY;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget   = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

CObj* CObjMgr::Get_ObjPointer(OBJ_ID eID)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	list<CObj*> pObjList = Get_ObjList(eID);

	if (!pObjList.empty())
	{
		CObj* pObj = pObjList.front();

		if (pObj != nullptr)
		{
			// 플레이어의 멤버 변수에 접근하는 코드 작성
			return pObj;
		}
	}
}
	

void CObjMgr::Add_Object(OBJ_ID eID, CObj* pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Initialize(void)
{
	m_bLoadPlayerPosition = false;

	Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create_Monster_Obj(65.f, -483.f, 60.f, 60.f, 20.f, DIR_LEFT));
	Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create_Monster_Obj(450.f, 528.f, 60.f, 60.f, 0.f, DIR_NONE));

	Add_Object(OBJ_DROPITEM, CAbstractFactory<CDropItem>::Create_Item_Obj(750.f, -305.f, 50.f, 50.f, IT_THUNDER));
	Add_Object(OBJ_TELEPORT, CAbstractFactory<CTeleport>::Create_Teleport_Obj(74.f, -1150.f, 50.f, 50.f, TT_TELEPORT_GODOWN));

	//1층 임시 텔폿
	Add_Object(OBJ_TELEPORT, CAbstractFactory<CTeleport>::Create_Teleport_Obj(355.f, 520.f, 50.f, 50.f, TT_TELEPORT_GOUP));

}

void CObjMgr::Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int	iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

}

void CObjMgr::Late_Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID		eID = iter->Get_RenderID();
			m_RenderList[eID].push_back(iter);
		}
	}

	CCollisionMgr::Get_Instance()->Collision_Teleport(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_TELEPORT]);
	CCollisionMgr::Get_Instance()->Collision_Rect(OBJ_PLAYER, m_ObjList[OBJ_PLAYER], OBJ_DROPITEM, m_ObjList[OBJ_DROPITEM]);
	CCollisionMgr::Get_Instance()->Collision_Shop(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_UI]);


 }

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc) ->bool
		{
			return pDst->Get_Info().fY < pSrc->Get_Info().fY;
		});

		for (auto& iter : m_RenderList[i])
			iter->Render(hDC);

		m_RenderList[i].clear();
	}
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJ_ID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

void CObjMgr::SavePlayerPosition()
{
	HANDLE hFile = CreateFile(L"../Data/PlayerPosition.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	WriteFile(hFile, &Get_ObjPointer(OBJ_PLAYER)->Get_Info(), sizeof(INFO), &dwByte, nullptr);

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Player Info Save 완료"), L"성공", MB_OK);
}

void CObjMgr::LoadPlayerPosition()
{
	m_bLoadPlayerPosition = true;

	HANDLE hFile = CreateFile(L"../Data/PlayerPosition.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD dwByte = 0;
	INFO tInfo{};

	//ReadFile(hFile, &PlayerInfo, sizeof(INFO), &dwByte, nullptr);

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create_Load_File_Obj(tInfo.fX,tInfo.fY));

	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Player Position Load 완료"), L"성공", MB_OK);
}

void CObjMgr::LoadPlayerPosition(float* pX, float* pY)
{
	m_bLoadPlayerPosition = true;

	HANDLE hFile = CreateFile(L"../Data/PlayerPosition.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD dwByte = 0;
	INFO tInfo{};

	//ReadFile(hFile, &PlayerInfo, sizeof(INFO), &dwByte, nullptr);

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create_Load_File_Obj(tInfo.fX, tInfo.fY));

	}

	*pX = tInfo.fX;
	*pY = tInfo.fY;

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Player Position Load 완료"), L"성공", MB_OK);
}