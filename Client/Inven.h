#pragma once
#include "Obj.h"

class CInven : public CObj
{
public:
	CInven();
	virtual ~CInven();

public:
	virtual void Initialize()	 override;
	virtual int  Update()		 override;
	virtual void Late_Update()   override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

private:
	void	Key_Input(void);

};

