#include "stdafx.h"
#include "Obj.h"

CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f), m_pFrameKey(L""),
	m_bGotHit(false), m_bTeleportCollision(false), m_bMerchantUpKey(false),
	m_bMerchantCollision(false)
{
	ZeroMemory(&m_tInfo,  sizeof(INFO));	
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tRect,  sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left   = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top    = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right  = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount64())
	{
		//++m_tFrame.iFrameStart;
		++m_tFrame.iFrameNow;

		m_tFrame.dwTime = GetTickCount64();

		if (m_tFrame.iFrameNow > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameNow = m_tFrame.iFrameStart;
			m_bGotHit = false;
		}
	}
}

void CObj::Move_One_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount64())
	{
		//++m_tFrame.iFrameStart;
		++m_tFrame.iFrameNow;

		m_tFrame.dwTime = GetTickCount64();

		if (m_tFrame.iFrameNow > m_tFrame.iFrameEnd)
		{
			m_bGotHit = false;
		}
	}
}

void CObj::Collision(OBJ_ID eObjId, CObj* pObj)
{
}