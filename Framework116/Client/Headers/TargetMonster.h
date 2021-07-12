#pragma once/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
#ifndef __TARGETMONSTER_H__/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
#include "GameObject.h"
/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
USING(Engine) /// ¾È¾¸ ¾È¾¸ ¾È¾¸ /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
class CTargetMonster final : public CGameObject/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
{/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
public:
	explicit CTargetMonster(LPDIRECT3DDEVICE9 pDevice);/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	explicit CTargetMonster(const CTargetMonster& other);/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual ~CTargetMonster() = default;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
										/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
public:/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual HRESULT Ready_GameObject_Prototype() override;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual _uint Update_GameObject(_float fDeltaTime) override;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual _uint Render_GameObject() override;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
											   /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
private:/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	_uint Movement(_float fDeltaTime);/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	_bool Collide_Check(_float fDeltaTime);/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
										   /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
public:/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	static CTargetMonster* Create(LPDIRECT3DDEVICE9 pDevice);/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual CGameObject * Clone(void * pArg = nullptr) override;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	virtual void Free() override;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
								 /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
private:/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	CTexture*	m_pTexture = nullptr;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	CTransform* m_pTransform = nullptr;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	CGeoMesh_Cylinder*  m_pGeoMesh = nullptr;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	CCollideSphere* m_pCollide = nullptr;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
										 /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
private:/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	_float m_fReviveTime = 5.f;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	_float m_fColTime = 0.f;/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
							/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
	_float4 vColorRGBA = { 0.8f, 0.f, 0.f, 0.f };/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
												 /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
};/// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
  /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
#define __TARGETMONSTER_H__ /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 
#endif/// ¾È¾¸ ¾È¾¸ ¾È¾¸ /// ¾È¾¸ ¾È¾¸ ¾È¾¸ 