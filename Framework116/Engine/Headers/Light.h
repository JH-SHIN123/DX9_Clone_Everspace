#pragma once

#ifndef __LIGHT_H__

#include "GameObject.h"

BEGIN(Engine)

enum class ELightType {
	Directional,
	PointLight,
	SpotLight,
	End
};

class ENGINE_DLL CLight final : public CGameObject
{
private:
	explicit CLight(LPDIRECT3DDEVICE9 pDevice);
	explicit CLight(const CLight& other);
	virtual ~CLight() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void* pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

public:
	static CLight* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	class CTransform* m_pTransform = nullptr;
	D3DLIGHT9 m_tLight;
	ELightType m_eLightType = ELightType::End;
};
END

#define __LIGHT_H__
#endif