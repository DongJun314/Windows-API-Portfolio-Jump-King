#pragma once
#include "Obj.h"

class CUi : public CObj
{
public:
	CUi();
	virtual ~CUi();

public:
	virtual void Initialize()	 override;
	virtual int  Update()		 override;
	virtual void Late_Update()   override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

	int Get_PreCursorIndex() { return m_iPreCursorIndex; }

private:
	TCHAR		m_szText[100];

	//Setting Menu
	float		m_fCursorY;
	int			m_iResumeX;
	int			m_iOptionsX;
	int			m_iInvenX;
	int			m_iSaveExitX;
	int			m_iGiveUpX;

	// Yes or No
	float		m_fYesOrNoCursorY;
	int			m_iAreYouSure;
	int			m_iNo;
	int			m_iYes;

	//Inventory
	float m_fInvenCursorY;
	int m_iCrown;
	int m_iKingShoes;
	int m_iGaintBoots;
	bool m_bCrown;
	bool m_bKingShoes;
	bool m_bGaintBoots;

	//상점때 쓸
	float m_fMerchantCursorY;
	int m_iCrownInShop;
	int m_iKingShoesInShop;
	int m_iGaintBootsInShop;
	bool m_bCrownInShop;
	bool m_bKingShoesInShop;
	bool m_bGaintBootsInShop;

	int m_iBack;

	//사용하지 않았음
	int			m_iPreCursorIndex;
};
