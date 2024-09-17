#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "Player.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
    :m_pObjList(nullptr)
{
}

CCollisionMgr::~CCollisionMgr()
{
    Release();
}

void CCollisionMgr::Initialize()
{
    m_pObjList = CObjMgr::Get_Instance()->Get_ObjListArr();
}

void CCollisionMgr::Update()
{

    // 플레이어 몬스터 충돌
    //if (!m_pObjList[OBJ_PLAYER].empty() && !m_pObjList[OBJ_MONSTER].empty())
    //{
    //   auto iter1 = m_pObjList[OBJ_PLAYER].begin();
    //   for (auto iter2 = m_pObjList[OBJ_MONSTER].begin(); iter2 != m_pObjList[OBJ_MONSTER].end();)
    //   {
    //      // Dst : 몬스터 , Src : 플레이어
    //      Vector2D vColDirFromSrc;   // 몬스터가 맞은 방향
    //      if (Interact_Rect(*(*iter1), *(*iter2), vColDirFromSrc))
    //      {
    //         // 몬스터가 플레이어에게 맞은 방향
    //         (*iter2)->OnCollisionObj(*iter1, vColDirFromSrc.Get_DirAngle_Rad());

    //         vColDirFromSrc *= -1.f;
    //         // 플에이어가 몬스터에게 맞은 방향
    //         (*iter1)->OnCollisionObj(*iter2, vColDirFromSrc.Get_DirAngle_Rad());
    //      }
    //   }
    //}

    // 플레이어 총알 충돌

    // 플레이어 상호작용구조물 충돌


}

void CCollisionMgr::Late_Update()
{
}

void CCollisionMgr::Render(HDC _hdc)
{
}

void CCollisionMgr::Release()
{
}
bool CCollisionMgr::Collision_Ground(float* _pY, INFO _tInfo, LINE_TYPE* _pLT, LINE_SHAPE* _pLS)
{
    *_pLT = LT_NONE;
    *_pLS = LS_NONE;

    // 라인리스트 받아오기
    list<CLine*>* tempList = CLineMgr::Get_Instance()->Get_LineList();
    if (tempList->empty()) return false;

    float fX = _tInfo.fX;
    float fY = _tInfo.fY;

    CLine* pLine = nullptr;

    for (auto& iter : *tempList)
    {
        float   x1 = iter->Get_Info().tLPoint.fX;
        float   y1 = iter->Get_Info().tLPoint.fY;
        float   x2 = iter->Get_Info().tRPoint.fX;
        float   y2 = iter->Get_Info().tRPoint.fY;

        // 수직선 체크 안함
        if ((int)(x1 - x2) == 0)
            continue;

        if (x1 < x2 && (fX < x1 || fX > x2))
            continue;

        if (x1 > x2 && (fX > x1 || fX < x2))
            continue;

        float tempY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
        if (tempY < fY)
            continue;

        if (pLine == nullptr)
        {
            *_pY = tempY;
            pLine = iter;
            continue;
        }

        if (tempY < *_pY)
        {
            *_pY = tempY;
            pLine = iter;
        }
    }

    if (nullptr == pLine)
    {
        return false;
    }

    *_pLT = pLine->Get_LineType();
    *_pLS = pLine->Get_LineShape();

    return true;
}

bool CCollisionMgr::Collision_Line_Horizontal(INFO& _tInfo, VECTOR2& _tVel, VECTOR2* _colPoint, DIRECTION* pDirection)
{
    _colPoint->fX = 0.f;
    _colPoint->fY = 0.f;

    *pDirection = DIR_NONE;

    float _fSafeX = _tInfo.fCX * 0.25f;
    float _fSafeY = _tInfo.fCY * 0.25f;

    list<CLine*>* tempList = CLineMgr::Get_Instance()->Get_LineList();
    if (tempList->empty()) return false;

    VECTOR2 tCurrentUp{ _tInfo.fX, _tInfo.fY - _tInfo.fCY * 0.49f };
    VECTOR2 tNextUp{ _tInfo.fX + _tVel.fX, _tInfo.fY + _tVel.fY - _tInfo.fCY * 0.49f };

    VECTOR2 tCurrentDown{ _tInfo.fX, _tInfo.fY + _tInfo.fCY * 0.49f };
    VECTOR2 tNextDown{ _tInfo.fX + _tVel.fX, _tInfo.fY + _tVel.fY + _tInfo.fCY * 0.49f };

    VECTOR2 tTempPoint{ 0.f, 0.f };

    CLine* pLine = nullptr;
    float fDistance;
    for (auto& iter : *tempList)
    {
        if ((int)(iter->Get_Info().tLPoint.fX - iter->Get_Info().tRPoint.fX) != 0)
            continue;

        VECTOR2 tLinePoint1{ iter->Get_Info().tLPoint.fX, iter->Get_Info().tLPoint.fY };
        VECTOR2 tLinePoint2{ iter->Get_Info().tRPoint.fX, iter->Get_Info().tRPoint.fY };

        if (GetIntersectPoint(tCurrentUp,
            tNextUp,
            tLinePoint1,
            tLinePoint2,
            &tTempPoint))
        {
            float fTempDistance = sqrtf(powf(tCurrentUp.fX - tTempPoint.fX, 2.f) + powf(tCurrentUp.fY - tTempPoint.fY, 2.f));

            if (nullptr == pLine)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX;
                _colPoint->fY = tTempPoint.fY + _tInfo.fCY * 0.5f;
                continue;
            }

            if (fDistance > fTempDistance)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX;
                _colPoint->fY = tTempPoint.fY + _tInfo.fCY * 0.5f;
            }
        }
        else if (GetIntersectPoint(tCurrentDown, tNextDown, tLinePoint1, tLinePoint2, &tTempPoint))
        {
            float fTempDistance = sqrtf(powf(tCurrentDown.fX - tTempPoint.fX, 2.f) + powf(tCurrentDown.fY - tTempPoint.fY, 2.f));

            if (nullptr == pLine)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX;
                _colPoint->fY = tTempPoint.fY - _tInfo.fCY * 0.5f;
                continue;
            }

            if (fDistance > fTempDistance)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX;
                _colPoint->fY = tTempPoint.fY - _tInfo.fCY * 0.5f;
            }
        }
    }

    if (pLine == nullptr)
        return false;

    if (_tVel.fX > 0)
    {
        *pDirection = DIR_RIGHT;
        return true;
    }
    else if (_tVel.fX < 0)
    {
        *pDirection = DIR_LEFT;
        return true;
    }

    return false;
}

bool CCollisionMgr::Collision_Line_Vertical(INFO& _tInfo, VECTOR2& _tVel, VECTOR2* _colPoint, DIRECTION* pDirection)
{
    _colPoint->fX = 0.f;
    _colPoint->fY = 0.f;

    *pDirection = DIR_NONE;

    float _fSafeX = _tInfo.fCX * 0.25f;
    float _fSafeY = _tInfo.fCY * 0.25f;

    list<CLine*>* tempList = CLineMgr::Get_Instance()->Get_LineList();
    if (tempList->empty()) return false;

    VECTOR2 tCurrentLeft{ _tInfo.fX - _tInfo.fCX * 0.49f, _tInfo.fY };
    VECTOR2 tNextLeft{ _tInfo.fX - _tInfo.fCX * 0.49f + _tVel.fX, _tInfo.fY + _tVel.fY };

    VECTOR2 tCurrentRight{ _tInfo.fX + _tInfo.fCX * 0.49f, _tInfo.fY };
    VECTOR2 tNextRight{ _tInfo.fX + _tInfo.fCX * 0.49f + _tVel.fX, _tInfo.fY + _tVel.fY };

    VECTOR2 tTempPoint{ 0.f, 0.f };

    CLine* pLine = nullptr;
    float fDistance;
    for (auto& iter : *tempList)
    {
        if ((int)(iter->Get_Info().tLPoint.fX - iter->Get_Info().tRPoint.fX) == 0)
            continue;

        VECTOR2 tLinePoint1{ iter->Get_Info().tLPoint.fX, iter->Get_Info().tLPoint.fY };
        VECTOR2 tLinePoint2{ iter->Get_Info().tRPoint.fX, iter->Get_Info().tRPoint.fY };

        if (GetIntersectPoint(tCurrentLeft,
            tNextLeft,
            tLinePoint1,
            tLinePoint2,
            &tTempPoint))
        {
            float fTempDistance = sqrtf(powf(tCurrentLeft.fX - tTempPoint.fX, 2.f) + powf(tCurrentLeft.fY - tTempPoint.fY, 2.f));

            if (nullptr == pLine)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX + _tInfo.fCX * 0.5f;
                _colPoint->fY = tTempPoint.fY;
                continue;
            }

            if (fDistance > fTempDistance)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX + _tInfo.fCX * 0.5f;
                _colPoint->fY = tTempPoint.fY;
            }
        }
        else if (GetIntersectPoint(tCurrentRight,
            tNextRight,
            tLinePoint1,
            tLinePoint2,
            &tTempPoint))
        {
            float fTempDistance = sqrtf(powf(tCurrentRight.fX - tTempPoint.fX, 2.f) + powf(tCurrentRight.fY - tTempPoint.fY, 2.f));

            if (nullptr == pLine)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX - _tInfo.fCX * 0.5f;
                _colPoint->fY = tTempPoint.fY;
                continue;
            }

            if (fDistance > fTempDistance)
            {
                pLine = iter;
                fDistance = fTempDistance;
                _colPoint->fX = tTempPoint.fX - _tInfo.fCX * 0.5f;
                _colPoint->fY = tTempPoint.fY;
            }
        }
    }

    if (pLine == nullptr)
        return false;

    if (_tVel.fY > 0)
    {
        *pDirection = DIR_DOWN;
        return true;
    }
    else if (_tVel.fY < 0)
    {
        *pDirection = DIR_UP;
        return true;
    }

    return false;
}

bool CCollisionMgr::GetIntersectPoint(const VECTOR2& AP1, const VECTOR2& AP2, const VECTOR2& BP1, const VECTOR2& BP2, VECTOR2* IP)
{
    float t;
    float s;
    float under = (BP2.fY - BP1.fY) * (AP2.fX - AP1.fX) - (BP2.fX - BP1.fX) * (AP2.fY - AP1.fY);
    if (under == 0) return false;

    float _t = (BP2.fX - BP1.fX) * (AP1.fY - BP1.fY) - (BP2.fY - BP1.fY) * (AP1.fX - BP1.fX);
    float _s = (AP2.fX - AP1.fX) * (AP1.fY - BP1.fY) - (AP2.fY - AP1.fY) * (AP1.fX - BP1.fX);

    t = _t / under;
    s = _s / under;

    if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
    if (_t == 0 && _s == 0) return false;

    IP->fX = AP1.fX + t * (float)(AP2.fX - AP1.fX);
    IP->fY = AP1.fY + t * (float)(AP2.fY - AP1.fY);

    return true;
}


int CCollisionMgr::Collision_RectEx(list<CObj*> Dst, list<CObj*> Src)
{
    float	fX = 0.f, fY = 0.f;


    for (auto& DstList : Dst)
    {
        for (auto& SrcList : Src)
        {
            if (Check_Rect(DstList, SrcList, &fX, &fY))
            {
                // 상하 충돌
                if (fX > fY)
                {
                    if (DstList->Get_Info().fY < SrcList->Get_Info().fY)
                    {
                        DstList->Set_PosY(-fY * 2.f);
                        DstList->Set_Dead();
                        SrcList->Set_Dead();
                        return CR_UP;
                    }
                    else // 하 충돌
                    {
                        DstList->Set_PosY(fY * 2.f);
                        return CR_DOWN;
                    }
                }
                // 좌우 충돌
                else
                {
                    if (DstList->Get_Info().fX < SrcList->Get_Info().fX)
                    {
                        DstList->Set_PosX(-fX * 20.f);
                        return CR_LEFT;
                    }
                    else // 우 충돌
                    {
                        DstList->Set_PosX(fX * 20.f);
                        return CR_RIGHT;
                    }
                }
            }
        }
    }

    return CR_NONE;
}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc,
    float* pX, float* pY)
{
    float		fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
    float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

    float		fCX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
    float		fCY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

    if ((fCX >= fWidth) && (fCY >= fHeight))
    {
        *pX = fCX - fWidth;
        *pY = fCY - fHeight;

        return true;
    }

    return false;
}

bool CCollisionMgr::Collision_Rect(OBJ_ID DstId, list<CObj*> DstList, OBJ_ID SrcId, list<CObj*> SrcList)
{
    RECT		rc{};

    for (auto& Dst : DstList)
    {
        if (Dst->Get_Dead())
            continue;

        for (auto& Src : SrcList)
        {
            if (Src->Get_Dead())
                continue;

            if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
            {
                Dst->Collision(SrcId, Src);
                Src->Collision(DstId, Dst);

                return true;
            }
        }
    }

    return false;
}

bool CCollisionMgr::Collision_Teleport(list<CObj*> Dst, list<CObj*> Src)
{
    RECT  rc{};

    for (auto& DstList : Dst)
    {
        for (auto& SrcList : Src)
        {
            if (IntersectRect(&rc, &(DstList->Get_Rect()), &(SrcList->Get_Rect())))
            {
                if (SrcList->Get_TeleportType() == TT_TELEPORT_GOUP)
                {
                   DstList->Set_TeleportType(TT_TELEPORT_GOUP);
                }
                else if (SrcList->Get_TeleportType() == TT_TELEPORT_GODOWN)
                {
                   DstList->Set_TeleportType(TT_TELEPORT_GODOWN);
                }
                DstList->Set_TeleportCollision();

                return DstList->Get_TeleportCollision();
            }
        }
    }
    return false;
}

bool CCollisionMgr::Collision_Shop(list<CObj*> Dst, list<CObj*> Src)
{
    RECT  rc{};

    for (auto& DstList : Dst)
    {
        for (auto& SrcList : Src)
        {
            if (IntersectRect(&rc, &(DstList->Get_Rect()), &(SrcList->Get_Rect())))
            {
                DstList->Set_MerchantCollision();

                return true;
            }
        }
    }
    return false;
}