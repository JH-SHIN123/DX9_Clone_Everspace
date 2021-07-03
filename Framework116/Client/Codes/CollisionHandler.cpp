#include"stdafx.h"
#include "CollisionHandler.h"
#include "Collision.h"

void CCollisionHandler::Collision_SphereToSphere(const wstring& wstrDstLayerTag, const wstring& wstrSrcLayerTag)
{
	const list<CGameObject*>* Dst_Layer = CManagement::Get_Instance()->Get_GameObjectList(wstrDstLayerTag);
	const list<CGameObject*>* Src_Layer = CManagement::Get_Instance()->Get_GameObjectList(wstrSrcLayerTag);

	if (nullptr == Dst_Layer) return;
	if (nullptr == Src_Layer) return;

	for(auto & dst : *Dst_Layer) 
	{
		if (nullptr == dst) continue;
		const vector<class CCollide*>* dstCollides = dst->Get_Collides();
		if (nullptr == dstCollides) continue;

		for (auto& src : *Src_Layer) 
		{
			if (nullptr == src) continue;
			const vector<class CCollide*>* srcCollides = src->Get_Collides();
			if (nullptr == srcCollides) continue;

			if (Check_Collides(dstCollides, srcCollides)) 
			{
				// Ãæµ¹ OK
				int i = 0;
				return;
			}
		}
	}
}

bool CCollisionHandler::Check_Collides(const vector<class CCollide*>* pDstCollides, const vector<class CCollide*>* pSrcCollides)
{
	for (auto& dst : *pDstCollides) 
	{
		if (nullptr == dst) continue;
		for (auto& src : *pSrcCollides)
		{
			if (nullptr == src) continue;
			if (CCollision::IntersectSphereToSphere(dst->Get_BoundingSphere(), src->Get_BoundingSphere()))
				return true;
		}
	}

	return false;
}
