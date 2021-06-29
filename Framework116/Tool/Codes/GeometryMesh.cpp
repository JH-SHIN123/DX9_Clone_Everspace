#include "pch.h"
#include "GeometryMesh.h"

CGeometryMesh::CGeometryMesh(LPDIRECT3DDEVICE9 pDevice, const EGeoMeshType eGeoType) :
	CComponent(pDevice),
	m_eGeoType(eGeoType)
{
}

CGeometryMesh::CGeometryMesh(const CGeometryMesh& other) : 
	CComponent(other),
	m_pMesh(other.m_pMesh),
	m_eGeoType(other.m_eGeoType)
{
	Safe_AddRef(m_pMesh);
}

HRESULT CGeometryMesh::Ready_Component_Prototype()
{
	CComponent::Ready_Component_Prototype();

	HRESULT hr;
	switch (m_eGeoType)
	{
	case EGeoMeshType::Cube:
		hr = D3DXCreateBox(m_pDevice, 1.f, 1.f, 1.f, &m_pMesh, nullptr);
		break;
	case EGeoMeshType::Cylinder:
		hr = D3DXCreateCylinder(m_pDevice, 1.f, 1.f, 1.f,10,10, &m_pMesh, nullptr);
		break;
	case EGeoMeshType::Sphere:
		hr = D3DXCreateSphere(m_pDevice, 1.f, 10,10, &m_pMesh, nullptr);
		break;
	case EGeoMeshType::Torus:
		hr = D3DXCreateTorus(m_pDevice, 1.f,2.f, 10, 10, &m_pMesh, nullptr);
		break;
	}

	if (FAILED(hr)) {
		PRINT_LOG(L"Error", L"Failed to Create GeometryMesh");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CGeometryMesh::Ready_Component(void* pArg)
{
	return S_OK;
}

_uint CGeometryMesh::Render_Mesh()
{
	m_pDevice->SetTexture(0,nullptr);
	m_pMesh->DrawSubset(0);

	return _uint();
}

CGeometryMesh* CGeometryMesh::Create(LPDIRECT3DDEVICE9 pDevice, const EGeoMeshType eGeoType)
{
	CGeometryMesh* pInstance = new CGeometryMesh(pDevice, eGeoType);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Texture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CGeometryMesh::Clone(void* pArg)
{
	CGeometryMesh* pClone = new CGeometryMesh(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Texture");
		Safe_Release(pClone);
	}

	return pClone;
}

void CGeometryMesh::Free()
{
	Safe_Release(m_pMesh);

	CComponent::Free();
}
