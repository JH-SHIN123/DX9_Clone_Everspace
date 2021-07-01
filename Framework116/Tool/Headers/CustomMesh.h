#pragma once

#ifndef __CUSTOM_MESH_H__

#include "Component.h"

USING(Engine)

class CCustomMesh final : public CComponent
{
private:
	explicit CCustomMesh(LPDIRECT3DDEVICE9 pDevice);
	explicit CCustomMesh(const CCustomMesh& other);
	virtual ~CCustomMesh() = default;

public:
	// 툴에서만 사용
	void Add_GeometryMesh(const class CGeometryMesh* pGeometryMesh);

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void* pArg = nullptr) override;
	virtual _uint	Render_Mesh();

public:
	static CCustomMesh* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	//vector<class CGeometryMesh*> m_vecGeoMesh;
	// Transform
};

#define __CUSTOM_MESH_H__
#endif