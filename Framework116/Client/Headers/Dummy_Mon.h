#pragma once
#ifndef __DUMMY_MON_H__

#include "GameObject.h"

USING(Engine)

class CDummy_Mon final : public CGameObject
{
public:
	explicit CDummy_Mon(LPDIRECT3DDEVICE9 pDevice);
	explicit CDummy_Mon(const CDummy_Mon& other);
	virtual ~CDummy_Mon() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

private:
	_uint Movement(_float fDeltaTime);

public:
	static CDummy_Mon* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	CMesh*  m_pMesh = nullptr;
	CTransform* m_pTransform = nullptr;
	CCollideSphere*	m_pCollide = nullptr;

private:
	POINT m_tCurCursorPos = { 0,0 };
	POINT m_tPrevCursorPos = { 0,0 };

private:
	PASSDATA_OBJECT m_tPassData;

};

#define __DUMMY_MON_H__
#endif