#pragma once

#ifndef __POINTLIGHT_H__

#include "Light.h"

USING(Engine)

class CPointLight final : public CLight
{
public:
	explicit CPointLight(LPDIRECT3DDEVICE9 pDevice);
	explicit CPointLight(const CPointLight& other);
	virtual ~CPointLight() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void* pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

public:
	static CPointLight* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	_float3 m_vOffset = { 0.f,0.f,0.f };
};


#define __POINTLIGHT_H__
#endif