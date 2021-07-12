#pragma once

#ifndef __HUD_EEFECT_H__
#define __HUD_EEFECT_H__

#include "UI.h"

USING(Engine)
class CHUD_Effect : public CUI
{
public:
	explicit CHUD_Effect(LPDIRECT3DDEVICE9 pDevice);
	explicit CHUD_Effect(const CHUD_Effect& other);
	virtual ~CHUD_Effect() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void* pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

public:
	static CHUD_Effect* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

};


#endif // __HUD_EEFECT_H__


