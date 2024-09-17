#pragma once
#include "Obj.h"

class CShop : public CObj
{
public:
	enum MERCHANTSTATE { MS_MERCHANT, MS_END };

public:
	CShop();
	virtual ~CShop();

public:
	virtual void Initialize()	 override;
	virtual int  Update()		 override;
	virtual void Late_Update()   override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

	void				Motion_Change();

private:
	MERCHANTSTATE      m_ePreState;
	MERCHANTSTATE      m_eCurState;
};

