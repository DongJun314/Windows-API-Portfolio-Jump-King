#pragma once
#include "Obj.h"

class CMonster :
	public CObj
{
public:
	enum MONSTERSTATE { MS_IDLE, MS_LEFT_WALK, MS_RIGHT_WALK, MS_DEAD, MS_END };

public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize()	 override;
	virtual int  Update()		 override;
	virtual void Late_Update()   override;
	virtual void Render(HDC hDC) override;
	void Motion_Change();
	virtual void Release()		 override;

//public:
//	void Set_Distance(float _fDis) { m_fDistance = _fDis; }

private:
	INFO m_tStartInfo;
	float m_fDistance;

	MONSTERSTATE      m_ePreState;
	MONSTERSTATE      m_eCurState;
};