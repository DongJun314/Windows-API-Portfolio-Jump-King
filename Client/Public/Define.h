#pragma once
#define		WINCX		 800
#define		WINCY		 600
#define		PURE		 = 0
#define		OBJ_NOEVENT	 0
#define		OBJ_DEAD	 1
#define		PI			 3.14f
#define		VK_MAX		 0xff
#define		PLAYERCX	 32
#define		PLAYERCY	 32

enum DIRECTION	  { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_NONE,  DIR_END };
enum OBJ_ID		  { OBJ_PLAYER, OBJ_MONSTER, OBJ_DROPITEM, OBJ_TELEPORT, OBJ_INVEN, OBJ_SHOP, OBJ_UI, OBJ_END };
enum SCENEID	  { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE_1, SC_STAGE_2, SC_END };
enum RENDERID	  { BG, GAMEOBJECT, EFFECT, FG, UI, RENDER_END };
enum CHANNELID	  { SOUND_EFFECT, SOUND_BGM, MAXCHANNEL };
enum ITEMTYPE	  { IT_THUNDER, IT_END };
enum TELEPORTTYPE { TT_TELEPORT_GOUP, TT_TELEPORT_GODOWN, TT_END };
enum COL_RECT     { CR_UP, CR_DOWN, CR_LEFT, CR_RIGHT,CR_NONE,CR_END };
enum HITDIRECTION { HDIR_LEFT, HDIR_RIGHT, HDIR_UP, HDIR_DOWN, HDIR_NONE, HDIR_END };
enum LINE_TYPE    { LT_NORMAL, LT_ICE, LT_NONE, LT_END };
enum LINE_SHAPE   { LS_GROUND, LS_CEILING, LS_LEFT_WALL, LS_RIGHT_WALL,LS_WALL, LS_RIGHT_DIAGONAL, LS_LEFT_DIAGONAL, LS_NONE, LS_END };

//추가함
struct LineInfo
{
	LINE_SHAPE eShape;
	// 다른 선 정보를 저장할 변수들 추가 가능
};

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;

typedef struct tagLinePoint
{
	float	fX;
	float	fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) { }

}LINEPOINT;

typedef struct tagLine
{
	tagLinePoint		tLPoint;
	tagLinePoint		tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(tagLinePoint _tLPoint, tagLinePoint _tRPoint)
		: tLPoint(_tLPoint), tRPoint(_tRPoint) { }
}LINE;

typedef struct tagFrame
{
	int			iFrameStart;
	int			iFrameNow;
	int			iFrameEnd;
	int			iMotion;
	DWORD		dwSpeed;
	DWORD		dwTime;

}FRAME;

struct CTagFinder
{
public:
	CTagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
};


template<typename T>
void		Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct DeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

//점프랑 관련된 좌표 구조체
typedef struct tagVector2
{
	float fX;
	float fY;

} VECTOR2;

extern	HWND	g_hWnd;
extern  float	g_fVolume;
extern	bool	g_bPause;
extern  int		g_iJumps;
extern	int		g_iFalls;