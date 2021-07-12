#include "stdafx.h"
#include "BoostEffect.h"

CBoostEffect::CBoostEffect(LPDIRECT3DDEVICE9 pDevice) 
	: CGameObject(pDevice)
{
}

CBoostEffect::CBoostEffect(const CBoostEffect& other)
	: CGameObject(other)
{
}

HRESULT CBoostEffect::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CBoostEffect::Ready_GameObject(void* pArg)
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
		L"Component_Texture_Boost",
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


	m_pPlayerTransform = (CTransform*)m_pManagement->Get_Component(L"Layer_Player", L"Com_Transform");
	if(m_pPlayerTransform)
		Safe_AddRef(m_pPlayerTransform);

	return S_OK;
}

_uint CBoostEffect::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	return IsBillboarding();
}

_uint CBoostEffect::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::Alpha, this)))
		return UPDATE_ERROR;

	return _uint();
}

_uint CBoostEffect::Render_GameObject()
{
	CGameObject::Render_GameObject();


	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Render_VIBuffer();

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return _uint();
}

_uint CBoostEffect::IsBillboarding()
{
	/* Y축 빌보드 */
	_float4x4 matView;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);

	_float4x4 matScale, matRotate, matTrans;
	
	D3DXMatrixScaling(&matScale, 100.f, 100.f, 100.f);
	
	D3DXMatrixIdentity(&matRotate);
	matRotate._11 = matView._11;
	matRotate._13 = matView._13;
	matRotate._31 = matView._31;
	matRotate._33 = matView._33;
	D3DXMatrixInverse(&matRotate, 0, &matRotate);

	_float4x4 matWorld;
	matWorld = matScale * matRotate;

	m_pTransform->Set_WorldMatrix(matWorld);

	return _uint();
}

CBoostEffect* CBoostEffect::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CBoostEffect* pInstance = new CBoostEffect(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBoostEffect::Clone(void* pArg)
{
	CBoostEffect* pClone = new CBoostEffect(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CBoostEffect::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pPlayerTransform);

	CGameObject::Free();
}
