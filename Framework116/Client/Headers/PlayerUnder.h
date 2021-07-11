#pragma once
#ifndef __PLAYER_UNDER_H__

#include "GameObject.h"


USING(Engine)
class CPlayerUnder final : public CGameObject
{
public:
	explicit CPlayerUnder(LPDIRECT3DDEVICE9 pDevice);
	explicit CPlayerUnder(const CPlayerUnder& other);
	virtual ~CPlayerUnder() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

private:
	_uint Movement(_float fDeltaTime);
public:
	static CPlayerUnder* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;


private:
	CTexture*	m_pTexture = nullptr;
	CTransform* m_pTransform = nullptr;
	CTransform* m_pPlayerTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
};

#define __PLAYER_UNDER_H__ 
#endif