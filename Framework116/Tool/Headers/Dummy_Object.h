#pragma once

#include "GameObject.h"

USING(Engine)
class CDummy_Object final : public CGameObject
{
private:
	explicit CDummy_Object(LPDIRECT3DDEVICE9 pDevice, const PASSDATA_OBJECT& tPASSDATA_OBJECT);
	explicit CDummy_Object(const CDummy_Object& other);
	virtual ~CDummy_Object() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;



public:
	static CDummy_Object* Create(LPDIRECT3DDEVICE9 pDevice, const PASSDATA_OBJECT& tPASSDATA_OBJECT);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	CMesh* m_pMesh = nullptr;
	CTransform* m_pTransform = nullptr;

private:
	PASSDATA_OBJECT m_tPassData;


};

