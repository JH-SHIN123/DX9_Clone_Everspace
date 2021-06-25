#include "stdafx.h"
#include "UI.h"

USING(Engine)

CUI::CUI(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CUI::CUI(const CUI& other)
	: CGameObject(other)
{
}

HRESULT CUI::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CUI::Ready_GameObject(void* pArg)
{
	CGameObject::Ready_GameObject(pArg);

	// For.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_VIBuffer_RectTexture",
		L"Com_VIBuffer",
		(CComponent**)&m_pVIBuffer)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_VIBuffer");
		return E_FAIL;
	}

	// For.Com_Texture
	if (FAILED(CGameObject::Add_Component(
		EResourceType::NonStatic,
		L"Component_Texture_Grass",
		L"Com_Texture",
		(CComponent**)&m_pTexture)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Texture");
		return E_FAIL;
	}

	// For.Com_Transform
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_Transform",
		L"Com_Transform",
		(CComponent**)&m_pTransform,
		pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
		return E_FAIL;
	}

	return S_OK;
}

_uint CUI::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	// 카메라 직교투영으로 변경?

	return m_pTransform->Update_Transform();
}

_uint CUI::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::UI, this)))
		return UPDATE_ERROR;

	//// 직교투영행렬 세팅



	//// 모든 UI들이 동일함
	//_float4x4 matOrtho;
	//D3DXMatrixOrthoLH(&matOrtho, );
	//m_pDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);

	IsBillboarding();

	return _uint();
}

_uint CUI::Render_GameObject()
{
	CGameObject::Render_GameObject();

	//_float4x4 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	//m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//
	//// 각각의 UI들마다 다름
	//_float4x4 matView;
	//D3DXMatrixIdentity(&matView);
	//matView._11 = 150.f;
	//matView._22 = 150.f;
	//matView._41 = 300.f;
	//m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	//_float4x4 matOrtho;
	//D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	//m_pDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);

	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Render_VIBuffer();

	return _uint();
}

_uint CUI::IsBillboarding()
{
	// View의 역행렬, 회전행렬(자전) 곱
	_float4x4 InvMatView;
	m_pDevice->GetTransform(D3DTS_VIEW, &InvMatView);
	InvMatView._41 = 0.f;
	InvMatView._42 = 0.f;
	InvMatView._43 = 0.f;
	D3DXMatrixInverse(&InvMatView, 0, &InvMatView);

	_float4x4 matWorld;
	D3DXMatrixIdentity(&matWorld);

	/*
	스 * 자 * 이 * 공 * 부
	*/
	TRANSFORM_DESC transDesc = m_pTransform->Get_TransformDesc();
	_float4x4 matScale, matRotate, matTrans;
	D3DXMatrixScaling(&matScale, transDesc.vScale.x, transDesc.vScale.y, transDesc.vScale.z);

	_float4x4 matRotateX, matRotateY, matRotateZ;
	D3DXMatrixRotationX(&matRotateX, transDesc.vRotate.x);
	D3DXMatrixRotationY(&matRotateY, transDesc.vRotate.y);
	D3DXMatrixRotationZ(&matRotateZ, transDesc.vRotate.z);
	matRotate = matRotateX * matRotateY * matRotateZ;

	D3DXMatrixTranslation(&matTrans, transDesc.vPosition.x, transDesc.vPosition.y, transDesc.vPosition.z);
	matWorld = matScale * InvMatView * matRotate * matTrans;

	m_pTransform->Set_WorldMatrix(matWorld);

	return _uint();
}

CUI* CUI::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CUI* pInstance = new CUI(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CUI::Clone(void* pArg)
{
	CUI* pClone = new CUI(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CUI::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);

	CGameObject::Free();
}
