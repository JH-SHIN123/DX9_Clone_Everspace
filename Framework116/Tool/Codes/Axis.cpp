#include "pch.h"
#include "..\Headers\Axis.h"
#include "Mesh.h"

CAxis::CAxis(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CAxis::CAxis(const CAxis & other)
	: CGameObject(other)
{
}

HRESULT CAxis::ChangeMesh(const wstring& wstrMeshPrototypeTag)
{
	// 기존꺼 m_pMesh 레퍼런스 카운팅 반납
	Safe_Release(m_pMesh);

	// 메시 교체
	auto iter_find = m_Components.find(L"Com_Mesh");
	if (m_Components.end() != iter_find)
	{
		// 실질적 메모리 해제 (클론삭제)
		Safe_Release(iter_find->second);

		// 새로운거로 변경
		CComponent* pClone = (CComponent*)m_pManagement->Clone_Component(EResourceType::Static, wstrMeshPrototypeTag);
		if (nullptr == pClone)
		{
			PRINT_LOG(L"Error", L"Failed to Change Mesh");
			return E_FAIL;
		}

		// 원본데이터(m_Components) 포인터지정
		iter_find->second = pClone;

		m_pMesh = (CMesh*)pClone;
		Safe_AddRef(pClone);

		m_wstrMeshPrototypeTag = wstrMeshPrototypeTag;
	}

	return S_OK;
}

HRESULT CAxis::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CAxis::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	// For.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_Mesh_Axis",
		L"Com_Mesh",
		(CComponent**)&m_pMesh)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Component_Mesh_Axis");
		return E_FAIL;
	}

	// For.Com_Transform
	TRANSFORM_DESC TransformDesc;
	TransformDesc.vScale = { 1.f,1.f,1.f };

	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_Transform",
		L"Com_Transform",
		(CComponent**)&m_pTransform,
		&TransformDesc)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
		return E_FAIL;
	}

	return S_OK;
}

_uint CAxis::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);	

	return m_pTransform->Update_Transform();
}

_uint CAxis::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::NonAlpha, this)))
		return UPDATE_ERROR;

	return _uint();
}

_uint CAxis::Render_GameObject()
{
	CGameObject::Render_GameObject();

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	
	m_pDevice->SetTexture(0, nullptr);
	if (m_pMesh)
		m_pMesh->Render_Mesh();

	return _uint();
}

_uint CAxis::Movement(_float fDeltaTime)
{
	return _uint();
}

CAxis * CAxis::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CAxis* pInstance = new CAxis(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CAxis::Clone(void * pArg/* = nullptr*/)
{
	CAxis* pClone = new CAxis(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CAxis::Free()
{
	Safe_Release(m_pMesh);
	Safe_Release(m_pTransform);

	CGameObject::Free();
}
