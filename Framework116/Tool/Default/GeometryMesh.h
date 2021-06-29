#pragma once

#ifndef __GEOMETRY_MESH_H__

#include "Component.h"

USING(Engine)
enum class EGeoMeshType {
	Cube = 0,
	Sphere,
	Cylinder,
	Torus
};

class CGeometryMesh final : public CComponent
{
private:
	explicit CGeometryMesh(LPDIRECT3DDEVICE9 pDevice, const EGeoMeshType eGeoType);
	explicit CGeometryMesh(const CGeometryMesh& other);
	virtual ~CGeometryMesh() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void* pArg = nullptr) override;
	virtual _uint	Render_Mesh();

public:
	static CGeometryMesh* Create(LPDIRECT3DDEVICE9 pDevice, const EGeoMeshType eGeoType);
	virtual CComponent* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	LPD3DXMESH m_pMesh = nullptr;
	EGeoMeshType m_eGeoType = EGeoMeshType::Cube;
};

#define __GEOMETRY_MESH_H__
#endif