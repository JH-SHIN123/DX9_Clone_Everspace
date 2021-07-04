#include "stdafx.h"
#include "PointLight.h"

CPointLight::CPointLight(LPDIRECT3DDEVICE9 pDevice)
	: CLight(pDevice)
{
}

CPointLight::CPointLight(const CPointLight& other)
	: CLight(other)
{
}

HRESULT CPointLight::Ready_GameObject_Prototype()
{
	CLight::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CPointLight::Ready_GameObject(void* pArg)
{
	CLight::Ready_GameObject(pArg);
	
	m_eLightType = ELightType::PointLight;

	// 플레이어와 얼만큼 떨어져있을지 오프셋 지정
	m_vOffset = { 800.f,500.f,800.f };

	return S_OK;
}

_uint CPointLight::Update_GameObject(_float fDeltaTime)
{
	CTransform* pTransform = (CTransform*)m_pManagement->Get_Component(L"Layer_Player",L"Com_Transform");
	if (nullptr != pTransform) {
		_float3 vPos = pTransform->Get_State(EState::Position);
		m_pTransform->Set_Position(vPos + m_vOffset);
	}

	return m_pTransform->Update_Transform();
}

_uint CPointLight::LateUpdate_GameObject(_float fDeltaTime)
{
	CLight::LateUpdate_GameObject(fDeltaTime);

	return _uint();
}

_uint CPointLight::Render_GameObject()
{
	return _uint();
}

CPointLight* CPointLight::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPointLight* pInstance = new CPointLight(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CPointLight::Clone(void* pArg)
{
	CPointLight* pClone = new CPointLight(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CPointLight::Free()
{
	CPointLight::Free();
}
