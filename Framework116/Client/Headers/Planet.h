#pragma once
<<<<<<< HEAD
=======

>>>>>>> main
#ifndef __PLANET_H__

#include "GameObject.h"

USING(Engine)
<<<<<<< HEAD
=======
typedef struct tagPlanetDesc : public BASE_DESC {
	wstring wstrTextureTag = L"";
	TRANSFORM_DESC tTransformDesc;
}PLANET_DESC;

>>>>>>> main
class CPlanet final : public CGameObject
{
public:
	explicit CPlanet(LPDIRECT3DDEVICE9 pDevice);
	explicit CPlanet(const CPlanet& other);
	virtual ~CPlanet() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
<<<<<<< HEAD
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
=======
	virtual HRESULT Ready_GameObject(void* pArg = nullptr) override;
>>>>>>> main
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

<<<<<<< HEAD
private:
	_uint Movement(_float fDeltaTime);

public:
	static CPlanet* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	CTexture*	m_pTexture = nullptr;
	CTransform* m_pTransform = nullptr;
	CGeoMesh_Sphere*  m_pMesh = nullptr;
	CCollideSphere* m_pCollide = nullptr;

private:
	_float m_fSpawnTime = 2.f;
	D3DMATERIAL9 m_tMatrial;
	_float4 m_vRGBA = { 1.f,1.f,1.f,1.f };

};

#define __PLANET_H__ 
=======
public:
	static CPlanet* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	CModelMesh*			m_pModelMesh = nullptr;
	CTransform*			m_pTransform = nullptr;
	CTexture*			m_pTexture = nullptr;
	CCollideSphere*		m_pCollide = nullptr;
};

#define __PLANET_H__
>>>>>>> main
#endif