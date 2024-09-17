#pragma once

#include "Scene.h"

class CMyMenu : public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void Initialize()    override;
	virtual int  Update()		 override;
	virtual void Late_Update()   override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

	void Key_Input(void);

private:
	TCHAR		m_szText[100];
	DWORD	dwTime;

	//�ʱ� ���� ȭ��
	int		m_iCursorIndex;
	float	m_fCursorY;
	bool	m_bStartMenu;
	int		m_iNewGameX;
	int		m_iOtherBabeX;
	int		m_iOptionsX;
	int		m_iExtraX;
	int		m_iQuitX;
	

	//Yes Or No ȭ��
	float   m_fYesOrNoCursorY;
	int     m_iYesOrNoCursorIndex;
	bool	m_bYesOrNo;
	int		m_iAreYouSure;
	int		m_iNo;
	int		m_iYes;
	//yes or No�޴����� ����ϴ� �Ұ�
	bool    m_bBackToPrevious;
	bool	m_bDestroyWindow;

	//Load
	bool  m_bLoad;

};
