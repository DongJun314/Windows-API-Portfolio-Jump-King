#pragma once
#include "Define.h"

class CObj;
class CLine;

class CCollisionMgr
{
private:
    CCollisionMgr();
    ~CCollisionMgr();

public:
    static CCollisionMgr* Get_Instance()
    {
        if (!m_pInstance)
        {
            m_pInstance = new CCollisionMgr;
        }

        return m_pInstance;
    }
    static void   Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

public:
    void   Initialize();
    void   Update();
    void   Late_Update();
    void   Render(HDC _hdc);
    void   Release();

public:
    //라인 충돌
    bool   Collision_Ground(float* _pY, INFO _tInfo, LINE_TYPE* _pLT, LINE_SHAPE* _pLS);
    bool   Collision_Line_Horizontal(INFO& _tInfo, VECTOR2& _tVel, VECTOR2* _colPoint, DIRECTION* pDirection);
    bool   Collision_Line_Vertical(INFO& _tInfo, VECTOR2& _tVel, VECTOR2* _colPoint, DIRECTION* pDirection);
    bool   GetIntersectPoint(const VECTOR2& AP1, const VECTOR2& AP2, const VECTOR2& BP1, const VECTOR2& BP2, VECTOR2* IP);

    //렉트 충돌
    int    Collision_RectEx(list<CObj*> Dst, list<CObj*> Src);
    bool   Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);
    bool   Collision_Rect(OBJ_ID DstId, list<CObj*> DstList, OBJ_ID SrcId, list<CObj*> SrcList);
    bool   Collision_Teleport(list<CObj*> Dst, list<CObj*> Src);
    bool   Collision_Shop(list<CObj*> Dst, list<CObj*> Src);

private:
    static CCollisionMgr*    m_pInstance;
    list<CObj*>*             m_pObjList;      // ObjMgr의 ObjList배열을 받아줄 포인터

};
