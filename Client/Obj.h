#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	void	Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void	Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	void	Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void	Set_PosX(float _fX) { m_tInfo.fX += _fX; }

	INFO	Get_Info() { return m_tInfo; }
	RECT	Get_Rect() { return m_tRect; }

	void	Set_Dead() { m_bDead = true; }
	bool	Get_Dead() { return m_bDead; }


	void	Set_TeleportCollision() { m_bTeleportCollision = true; }
	bool	Get_TeleportCollision() { return m_bTeleportCollision; }
	void	Set_TeleportType(TELEPORTTYPE _eTT) { m_eTT = _eTT; }
	int		Get_TeleportType() { return m_eTT; }

	void	Set_MerchantCollision() { m_bMerchantCollision = true; }
	bool	Get_MerchantCollision() { return m_bMerchantCollision; }

	void	Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	//추후에 아이템으로 바꿀 예정
	void	Set_Rect(float _left, float _top, float _right, float _bottom)
	{
		m_tRect.left = _left;
		m_tRect.top = _top;
		m_tRect.right = _right;
		m_tRect.bottom = _bottom;
	}
	//새로 추가 렉트 사이즈
	void	Set_Size(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}
	//새로 추가
	void    Set_ItemType(ITEMTYPE eIT) { m_eIT = eIT; }
	ITEMTYPE		Get_ItemType() { return m_eIT; }

	void	Set_MonsterDirection(DIRECTION _eDir) { m_eDir = _eDir; }
	void	Set_Direction(float _fDirRad) { m_fDirRad = _fDirRad; }
	void	Set_HitDirection(HITDIRECTION _eHDir) { m_eHDir = _eHDir; }
	const RENDERID		Get_RenderID() const { return m_eRender; }


public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;
	virtual void		Collision(OBJ_ID eObjId, CObj* pObj);

protected:
	void				Update_Rect();
	void				Move_Frame();
	void				Move_One_Frame();

protected:
	DIRECTION		m_eDir;
	HITDIRECTION	m_eHDir;
	ITEMTYPE		m_eIT;
	TELEPORTTYPE	m_eTT;
	INFO			m_tInfo;
	RECT			m_tRect;



	FRAME		m_tFrame;
	RENDERID	m_eRender;

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	bool		m_bDead;
	bool		m_bGotHit;
	bool		m_bTeleportCollision;
	bool		m_bMerchantCollision;
	bool		m_bMerchantUpKey;
	float		m_fSpeed;
	float		m_fAngle;

	//몬스터 때문에 추가
	float		m_fCurHp;
	float		m_fMaxHp;
	float		m_fAttackPower;
	float		m_fDirRad;

};


