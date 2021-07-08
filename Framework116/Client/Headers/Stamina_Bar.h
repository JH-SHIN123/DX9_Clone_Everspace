#pragma once
#ifndef __STAMINA_BAR_H__

#include "GameObject.h"

USING(Engine)
class CStamina_Bar final : public CUI
{
public:
	enum MAKERID {MAKER_PLAYER, MAKER_BOSS_MONSTER, MAKER_MONSTER, MAKER_END};

public:
	explicit CStamina_Bar(LPDIRECT3DDEVICE9 pDevice);
	explicit CStamina_Bar(const CStamina_Bar& other);
	virtual ~CStamina_Bar() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

public:
	// ÇÇ±ð´Â¿ëµµ!
	void Set_ScaleX(_float _fDamage);
	_uint Who_Make_Me(MAKERID _iMakerName);

private:
	_uint Movement(_float fDeltaTime);
	_uint Adjust_Pos(_float fDeltaTime);

public:
	static CStamina_Bar* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	const list<class CGameObject*>* m_listCheckMonsters = nullptr;
	_float3 vTargetPos = {};
	MAKERID m_eMakerID = MAKER_END;
	
};

#define __STAMINA_BAR_H__
#endif