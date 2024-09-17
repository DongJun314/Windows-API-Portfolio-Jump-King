#pragma once

#include "Player.h"
#include "AbstractFactory.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	//추후에 몬스터가 플레이어 따라다니는 기능을 위한 함수
	CObj*		Get_Target(OBJ_ID eID, CObj* pObj);
	CObj*		Get_ObjPointer(OBJ_ID eID);

public:
	void		Add_Object(OBJ_ID eID, CObj* pObj);
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJ_ID eID);

	void		SavePlayerPosition();
	void		LoadPlayerPosition();
	void		LoadPlayerPosition(float* pX, float* pY);

	bool Get_LoadPlayerPosition() { return m_bLoadPlayerPosition; }


	list<CObj*>* Get_ObjListArr() { return m_ObjList; }
	list<CObj*> Get_ObjList(OBJ_ID eID) { return m_ObjList[eID]; }

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderList[RENDER_END];
	static CObjMgr* m_pInstance;

	bool m_bLoadPlayerPosition;
};