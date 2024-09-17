#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:
	enum PLAYERSTATE { PS_IDLE, PS_WALK, PS_CHARGING, PS_JUMPING, PS_ATTACK, PS_HIT, PS_MONSTER_HIT, PS_DEAD, PS_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void   Set_State(PLAYERSTATE _eCurState) { m_eCurState = _eCurState; }

public:
	virtual void Initialize()    override;
	virtual int  Update()        override;
	virtual void Late_Update()   override;
	virtual void Render(HDC hDC) override;
	virtual void Release()       override;
	virtual void Collision(OBJ_ID eObjId, CObj* pObj) override;

private:
	void   Key_Input(void);
	void   Motion_Change();
	void   Move();
	void   TeleportToAnotherScene();

	void   TouchLine(const LineInfo& lineInfo);

private:
	PLAYERSTATE      m_ePreState;
	PLAYERSTATE      m_eCurState;
	VECTOR2          m_tVelocity;
	VECTOR2          m_tForce;
	DWORD		     m_dwTime;

	bool             m_bLeftPressed;
	bool             m_bRightPressed;
	bool             m_bOnGround;
	bool             m_bJumping;
	bool             m_bFalling;
	bool			 m_bJump;
	bool             m_bCharging;
	bool	         m_bIsFlipped;

	bool			 m_bWind;
	bool			 m_bIce;

	DIRECTION		 m_eMoveDir;
	LineInfo		 m_tLineInfo;
	LINE_SHAPE		 m_eTouchedLineShape = LS_END;
			 
	float            m_fJumpSpeed;
	float            m_fJumpTime;
	float            m_fChargingValue;
	float            m_fChargingValueDel;
	float            m_fChargingValueMin;
	float            m_fChargingValueMax;
	float            m_fChargingStartTime;


			      
};