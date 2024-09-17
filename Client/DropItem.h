#pragma once
#include "Define.h"
#include "Obj.h"

class CDropItem : public CObj
{
public:
	enum DROPITEMSTATE { DIS_IDLE, DIS_TELEPORT, DIS_END};

public:
	CDropItem();
	virtual~CDropItem();

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		Late_Update()	override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release()		override;
	virtual void Collision(OBJ_ID eObjId, CObj* pObj) override;

	void				Motion_Change();

private:
	DROPITEMSTATE      m_ePreState;
	DROPITEMSTATE      m_eCurState;

	DWORD m_dwTime;
};