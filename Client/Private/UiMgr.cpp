#include "stdafx.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;

bool g_bPause = false;

CUiMgr::CUiMgr()
{
	m_pInven = nullptr;
	m_pShop = nullptr;
	m_iCursorIndex = 0;

	//Yes or No
	m_bYesOrNo = false;
	m_iYesOrNoCursorIndex = 0;
	m_bDestroyWindow = false;
	m_bBackToPrevious = false;

	//�κ��丮 
	m_bInventory = false;
	m_iInvenCursorIndex = 0;
	m_bCrown = false;
	m_bKingShoes = false;
	m_bGiantBoots = false;

	//���� 
	m_bMerchant = false;
	m_bCheckWhetherPressedMerchant = false;
	m_iMerchantCursorIndex = 0;
	m_bCrownInShop = false;
	m_bKingShoesInShop =false;
	m_bGiantBootsInShop = false;

	//����
	m_bSave = false;

}

CUiMgr::~CUiMgr()
{
}

void CUiMgr::Initialize()
{
	//m_iCursorIndex = m_pUi->Get_PreCursorIndex();
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CInven>::Create_Inventory_Obj(230.f, 130.f + fScrollY, 400, 220));

	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CShop>::Create_Shop_Obj(43.f, 275.f, 64.f, 64.f));
	//����ȭ��
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CUi>::Create_Setting_Menu_Obj(400.f, 300.f, 800.f, 600.f));
	//����ȭ�� Ŀ��
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CUi>::Create_Setting_Menu_Obj(550.f, 66.f, 11.f, 11.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CUi>::Create_Setting_Menu_Obj(500.f, 200.f, 220.f, 165.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CUi>::Create_Setting_Menu_Obj(500.f, 200.f, 220.f, 199.f));

	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CInven>::Create_Inventory_Obj(673.f, 130.f, 200, 220));

	/*m_pUi = CObjMgr::Get_Instance()->Get_ObjPointer(OBJ_UI);
	m_iCursorIndex = dynamic_cast<CUi*>(m_pUi)->Get_PreCursorIndex();*/
}

void CUiMgr::Release()
{
}

void CUiMgr::Update()
{
	Key_Input();
}

void CUiMgr::Late_Update()
{

}

void CUiMgr::Render_Font(HDC hdc, TCHAR* text, int fontSize, int x, int y, const TCHAR* fontName, size_t align, UINT color)
{
	// ��Ʈ ����
	HFONT font = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontName);

	HFONT oldFont = (HFONT)SelectObject(hdc, font);

	// ����� �����ϰ� ����
	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, align);
	//SetTextAlign(hdc, TA_LEFT | align);
	SetTextColor(hdc, color);

	// �ؽ�Ʈ ���
	TextOut(hdc, x, y, text, wcslen(text));

	// ���ҽ� ����
	SelectObject(hdc, oldFont);
	DeleteObject(font);
}

void CUiMgr::Key_Input(void)
{
	//�� ����Ű
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);

		//�ʱ� ���� �޴�
		if (!m_bYesOrNo && !m_bInventory && !m_bMerchant)
		{
			m_iCursorIndex--;
			if (m_iCursorIndex <= 0)
			{
				m_iCursorIndex = 0;
			}
		}
		//Yes or No �޴�
		if (m_bYesOrNo)
		{
			m_iYesOrNoCursorIndex--;
			if (m_iYesOrNoCursorIndex <= 0)
			{
				m_iYesOrNoCursorIndex = 0;
			}
		}
		//�κ��丮 �޴�
		if (m_bInventory)
		{
			m_iInvenCursorIndex--;
			if (m_iInvenCursorIndex <= 0)
			{
				m_iInvenCursorIndex = 0;
			}
		}
		//���� �޴�

		if (m_bMerchant && !m_bYesOrNo && !m_bInventory)
		{
			m_iMerchantCursorIndex--;
			if (m_iMerchantCursorIndex <= 0)
			{
				m_iMerchantCursorIndex = 0;
			}

		}
	}

	//�Ʒ� ����Ű
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);

		//�ʱ� ���� �޴�
		if (!m_bYesOrNo && !m_bInventory && !m_bMerchant)
		{
			m_iCursorIndex++;
			if (m_iCursorIndex >= 4)
			{
				m_iCursorIndex = 4;
			}
		}
		//Yes or No �޴�
		if (m_bYesOrNo)
		{
			m_iYesOrNoCursorIndex++;
			if (m_iYesOrNoCursorIndex >= 1)
			{
				m_iYesOrNoCursorIndex = 1;
			}
		}
		//�κ��丮 �޴�
		if (m_bInventory)
		{
			m_iInvenCursorIndex++;
			if (m_iInvenCursorIndex >= 3)
			{
				m_iInvenCursorIndex = 3;
			}
		}
		//���� �޴�
		if (m_bMerchant && !m_bYesOrNo && !m_bInventory)
		{
			m_iMerchantCursorIndex++;
			if (m_iMerchantCursorIndex >= 3)
			{
				m_iMerchantCursorIndex = 3;
			}
		}
	}

	//�ʱ� ���� �޴� (����Ű)
	if (!m_bYesOrNo && !m_bInventory && !m_bMerchant)
	{
		if (m_iCursorIndex == 0)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				if (m_bCheckWhetherPressedMerchant)
				{
					m_bMerchant = CCollisionMgr::Get_Instance()->Collision_Shop(
						CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER),
						CObjMgr::Get_Instance()->Get_ObjList(OBJ_UI));

					m_bCheckWhetherPressedMerchant = false;
				}
				g_bPause = false;
				CSoundMgr::Get_Instance()->PlayBGM(L"Nature bg.wav", g_fVolume);
			}
		}
		else if (m_iCursorIndex == 1)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);

				m_bInventory = true;
			}
		}
		else if (m_iCursorIndex == 2)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				//m_bYesOrNo = true;
			}
		}
		else if (m_iCursorIndex == 3)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bSave = true;
				m_bYesOrNo = true;
			}
		}
		else if (m_iCursorIndex == 4)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bYesOrNo = true;
			}
		}
	}
	//�κ��丮 �޴�
	if (m_bInventory)
	{
		if (m_iInvenCursorIndex == 0)
		{
			if (!m_bCrown)
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && !m_bYesOrNo && !m_bMerchant)
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bCrown = true;
				}
			}
			else
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bCrown = false;
				}
			}
		}
		else if (m_iInvenCursorIndex == 1)
		{

			if (!m_bKingShoes)
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bKingShoes = true;
					m_bGiantBoots = false;
				}
			}
			else
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bKingShoes = false;
				}
			}
		}
		else if (m_iInvenCursorIndex == 2)
		{
			if (!m_bGiantBoots)
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bGiantBoots = true;
					m_bKingShoes = false;
				}
			}
			else
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bGiantBoots = false;
				}
			}
		}
		else if (m_iInvenCursorIndex == 3)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bBackToPrevious = true;
			}
		}
	}

	////////////////////////////////����/////////////////////////////////////
	if (m_bMerchant)
	{
		m_bCheckWhetherPressedMerchant = true;

		if (!m_bYesOrNo)
		{
			if (m_iMerchantCursorIndex == 0)
			{
				if (!m_bCrownInShop)
				{
					if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
					{
						CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
						m_bYesOrNo = true;
					}
				}
			}
			else if (m_iMerchantCursorIndex == 1)
			{
				if (!m_bKingShoesInShop)
				{
					if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
					{
						CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
						m_bYesOrNo = true;
					}
				}
			}
			else if (m_iMerchantCursorIndex == 2)
			{
				if (!m_bGiantBootsInShop)
				{
					if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
					{
						CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
						m_bYesOrNo = true;
					}
				}
			}
			else if (m_iMerchantCursorIndex == 3)
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bMerchant = false;
				}
			}
		}

		if (m_bYesOrNo)
		{
			//Yes
			if (m_iYesOrNoCursorIndex == 0)
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bBackToPrevious = true;

					if (m_iMerchantCursorIndex == 0)
						m_bCrownInShop = true;
					if (m_iMerchantCursorIndex == 1)
						m_bKingShoesInShop = true;
					if (m_iMerchantCursorIndex == 2)
						m_bGiantBootsInShop = true;

				}
			}
			//No
			else if (m_iYesOrNoCursorIndex == 1)
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
					m_bDestroyWindow = true;

				}
			}
		}
	}

	//Yes or No �޴� & Merchant�ƴҶ�
	
	if (m_bYesOrNo && !m_bMerchant && !m_bSave)
	{
		if (m_iYesOrNoCursorIndex == 0)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && m_bYesOrNo && !m_bMerchant)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bDestroyWindow = true;
			}
		}
		else if (m_iYesOrNoCursorIndex == 1)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && m_bYesOrNo && !m_bMerchant)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bBackToPrevious = true;
			}
		}
	}

	if (m_bYesOrNo && !m_bMerchant && m_bSave)
	{
		if (m_iYesOrNoCursorIndex == 0)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && m_bYesOrNo && !m_bMerchant)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bDestroyWindow = true;
			}
		}
		else if (m_iYesOrNoCursorIndex == 1)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && m_bYesOrNo && !m_bMerchant)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"selectA.wav", SOUND_EFFECT, g_fVolume);
				m_bBackToPrevious = true;
			}
		}
	}

	//�����޴� ������
	if (!g_bPause)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

			CSoundMgr::Get_Instance()->PlaySound(L"menu_open.wav", SOUND_EFFECT, g_fVolume);
			m_bMerchant = false;
			m_bYesOrNo = false;
			g_bPause = true;
		}
	}
}

	


