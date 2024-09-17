#pragma once
#include "Define.h"
#include "Obj.h"

class CTeleport : public CObj
{
public:
	enum TELEPORTSTATE { DIS_TELEPORT, DIS_END };

public:
	CTeleport();
	virtual~CTeleport();

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		Late_Update()	override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release()		override;

	void				Motion_Change();

private:
	TELEPORTSTATE      m_ePreState;
	TELEPORTSTATE      m_eCurState;
};

