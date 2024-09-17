#pragma once
#include "Scene.h"
class CStage1 : public CScene
{
public:
	CStage1();
	virtual ~CStage1();

public:
	virtual void Initialize()	 override;
	virtual int  Update()		 override;
	virtual void Late_Update()	 override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

	HBITMAP GetRotatedBitmap(HDC hdc, HBITMAP hBitmap, float radians, COLORREF clrBack);

private:

	HBITMAP		m_hBitmap;
};
