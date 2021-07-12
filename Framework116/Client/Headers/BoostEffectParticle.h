#pragma once

#ifndef __BOOST_EFFECT_PARTICLE_H__

#include "GameObject.h"

USING(Engine)

class CBoostEffectParticle final : public CGameObject
{
public:
	explicit CBoostEffectParticle(LPDIRECT3DDEVICE9 pDevice);
	explicit CBoostEffectParticle(const CBoostEffectParticle& other);
	virtual ~CBoostEffectParticle() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void* pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

public:
	static CBoostEffectParticle* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTexture = nullptr;
	_float4x4	m_matWorld;

private:
	_float m_fLifeDeltaT = 0.f;
	_float m_fLifeTime = 2.f;
};

#define __BOOST_EFFECT_PARTICLE_H__ 
#endif