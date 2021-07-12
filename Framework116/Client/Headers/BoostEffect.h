#pragma once
#ifndef __BOOST_EFFECT_H__

#include "GameObject.h"

USING(Engine)

class CBoostEffect final : public CGameObject
{
public:
	explicit CBoostEffect(LPDIRECT3DDEVICE9 pDevice);
	explicit CBoostEffect(const CBoostEffect& other);
	virtual ~CBoostEffect() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void* pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

private:
	_uint IsBillboarding();

public:
	static CBoostEffect* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	CVIBuffer* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	
	CTransform* m_pTransform = nullptr;
	CTransform* m_pPlayerTransform = nullptr;
};

#define __BOOST_EFFECT_H__ 
#endif