#include "stdafx.h"
#include "..\Headers\LobbyCam.h"
#include"Pipeline.h"
CLobbyCam::CLobbyCam(LPDIRECT3DDEVICE9 pDevice)
	: CCamera(pDevice)
{
}

CLobbyCam::CLobbyCam(const CLobbyCam & other)
	: CCamera(other)
	, m_fDistanceFromTarget(other.m_fDistanceFromTarget)
	, m_fCamAngle(other.m_fCamAngle)
{
}

HRESULT CLobbyCam::Ready_GameObject_Prototype()
{
	CCamera::Ready_GameObject_Prototype();

	return S_OK;
}
 
HRESULT CLobbyCam::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CCamera::Ready_GameObject(pArg);

	m_pPlayerTransform = (CTransform*)m_pManagement->Get_Component(L"Layer_Lobby_Model", L"Com_Transform");
	Safe_AddRef(m_pPlayerTransform);
	if (nullptr == m_pPlayerTransform)
	{
		PRINT_LOG(L"Error", L"m_pPlayerTransform is nullptr");
		return E_FAIL;
	}

	return S_OK;
}

_uint CLobbyCam::Update_GameObject(_float fDeltaTime)
{
	CCamera::Update_GameObject(fDeltaTime);
	OffSet(fDeltaTime);
	return NO_EVENT;
}

_uint CLobbyCam::LateUpdate_GameObject(_float fDeltaTime)
{
	CCamera::LateUpdate_GameObject(fDeltaTime);

	return _uint();
}

_uint CLobbyCam::Render_GameObject()
{
	CCamera::Render_GameObject();

	return _uint();
}




_uint CLobbyCam::OffSet(_float fDeltaTime)
{

	m_fDistanceFromTarget = 10.f;
	m_CameraDesc.vAt = m_pPlayerTransform->Get_TransformDesc().vPosition;
	_float3 vEye = m_CameraDesc.vAt;
	vEye.x += m_fDistanceFromTarget;
	vEye.y += m_fDistanceFromTarget/2.f;
	vEye.z += m_fDistanceFromTarget;
	m_CameraDesc.vEye = vEye;
	return 0;
}

CLobbyCam * CLobbyCam::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLobbyCam* pInstance = new CLobbyCam(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create MainCam");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLobbyCam::Clone(void * pArg/* = nullptr*/)
{
	CLobbyCam* pClone = new CLobbyCam(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone MainCam");
		Safe_Release(pClone);
	}

	return pClone;
}

void CLobbyCam::Free()
{
	Safe_Release(m_pPlayerTransform);

	CCamera::Free();
}
