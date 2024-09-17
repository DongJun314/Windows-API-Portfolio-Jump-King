#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
	ZeroMemory(m_bKeyStateUp, sizeof(m_bKeyStateUp));
	ZeroMemory(m_bKeyStateDown, sizeof(m_bKeyStateDown));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(int _iKey)
{
	if ((!m_bKeyStateDown[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyStateDown[_iKey] = !m_bKeyStateDown[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyStateDown[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyStateDown[i] = !m_bKeyStateDown[i];
	}

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if (m_bKeyStateUp[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyStateUp[_iKey] = !m_bKeyStateUp[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyStateUp[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyStateUp[i] = !m_bKeyStateUp[i];
	}

	return false;
}