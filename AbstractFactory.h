#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory()  {}
	~CAbstractFactory() {}

public:
	static CObj* Create_Obj()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create_Load_File_Obj(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}

	//새로 추가
	static CObj* Create_Item_Obj(float _fX, float _fY, float _fCX, float _fCY, ITEMTYPE _eIT) 
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Initialize();

		pObj->Set_ItemType(_eIT);

		return pObj;
	}

	//새로 추가 몬스터
	static CObj* Create_Monster_Obj(float _fX, float _fY, float _fCX, float _fCY, float _fDis, DIRECTION eDir = DIR_END)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Initialize();

		pObj->Set_MonsterDirection(eDir);
		pObj->Set_Direction(_fDis);

		return pObj;
	}

	static CObj* Create_Teleport_Obj(float _fX, float _fY, float _fCX, float _fCY, TELEPORTTYPE _eTT)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Initialize();

		pObj->Set_TeleportType(_eTT);

		return pObj;
	}

	static CObj* Create_Inventory_Obj(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Initialize();

		//pObj->Set_TeleportType(_eTT);

		return pObj;
	}

	static CObj* Create_Shop_Obj(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Initialize();

		//pObj->Set_TeleportType(_eTT);

		return pObj;
	}

	static CObj* Create_Setting_Menu_Obj(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Initialize();

		return pObj;
	}
};