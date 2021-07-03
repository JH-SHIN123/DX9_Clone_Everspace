#pragma once

#ifndef __COLLISION_HANDLER_H__

USING(Engine)

class CCollisionHandler final
{
private:
	CCollisionHandler() = default;
	~CCollisionHandler() = default;

public:
	static void Collision_SphereToSphere(const wstring& wstrDstLayerTag, const wstring& wstrSrcLayerTag);

private:
	static bool Check_Collides(const vector<class CCollide*>* pDstCollides, const vector<class CCollide*>* pSrcCollides);
};

#define __COLLISION_HANDLER_H__
#endif // !__COLLISION_HANDLER_H__