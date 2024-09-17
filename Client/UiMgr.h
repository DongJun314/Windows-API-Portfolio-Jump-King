#pragma once
#include "Obj.h"
#include "Inven.h"
#include "Shop.h"
#include "Ui.h"

class CUiMgr
{
private:
	CUiMgr();
	~CUiMgr();

public:
	static CUiMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUiMgr;
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

public:
	void Initialize(void);
	void Release(void);
	void Update(void);
	void Late_Update(void);
	void Render_Font(HDC hdc, TCHAR* text, int fontSize, int x, int y, const TCHAR* fontName, size_t align, UINT color);

public:
	void Key_Input(void);

	//커서 인덱스값
	int Get_CursorIndex() { return m_iCursorIndex; }
	int Get_YesOrNoCursorIndex() { return m_iYesOrNoCursorIndex; }
	int Get_InvenCursorIndex() { return m_iInvenCursorIndex; }
	int Get_MerchantCursorIndex() { return m_iMerchantCursorIndex; }

	//Yes or No
	bool Get_YesOrNo() { return m_bYesOrNo; }
	void Set_YesOrNo() {m_bYesOrNo = false;}
	//게임 종료
	bool Get_DestroyWindow() { return m_bDestroyWindow; }
	void Set_DestroyWindow() { m_bDestroyWindow = false; }
	bool Get_BackToPrevious() { return m_bBackToPrevious; }
	void Set_BackToPrevious() { m_bBackToPrevious = false; }

	//인벤토리
	bool Get_Inventory() { return m_bInventory; }
	void Set_Inventory() { m_bInventory = false; }
	bool Get_Crown() { return m_bCrown; }
	bool Get_KingShoes() { return m_bKingShoes; }
	bool Get_GiantBoots() { return m_bGiantBoots; }

	//상점
	bool Get_Merchant() { return m_bMerchant; }
	bool Get_CheckWhetherPressedMerchant() { return m_bCheckWhetherPressedMerchant; }
	void Set_Merchant(bool bMerchant) { m_bMerchant = bMerchant; }
	bool Get_Merchant_Crown() { return m_bCrownInShop; }
	bool Get_Merchant_KingShoes() { return m_bKingShoesInShop; }
	bool Get_Merchant_GiantBoots() { return m_bGiantBootsInShop; }

	//저장
	bool Get_Save() { return m_bSave; }
	void Set_Save() { m_bSave = false; }
	

private:
	list<CObj*>		m_UiList[OBJ_END];
	static CUiMgr*  m_pInstance;

	CInven* m_pInven;
	CShop* m_pShop;
	CObj* m_pUi;

	int m_iCursorIndex;
	int m_iYesOrNoCursorIndex;
	int m_iInvenCursorIndex;
	int m_iMerchantCursorIndex;

	bool m_bYesOrNo;
	bool m_bBackToPrevious;
	bool m_bDestroyWindow;

	//인벤토리 화면 
	bool m_bInventory;
	bool m_bCrown;
	bool m_bKingShoes;
	bool m_bGiantBoots;

	//상점
	bool m_bMerchant;
	bool m_bCrownInShop;
	bool m_bKingShoesInShop;
	bool m_bGiantBootsInShop;
	bool m_bCheckWhetherPressedMerchant;

	//저장
	bool m_bSave;
};
