#include "stdafx.h"
#include "..\Headers\PlayerUnder.h"
#include "MaterialHandler.h"
#include"Pipeline.h"
#include"LobbyCam.h"
#include"Lobby.h"

CPlayerUnder::CPlayerUnder(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CPlayerUnder::CPlayerUnder(const CPlayerUnder & other)
	: CGameObject(other)
{

}

HRESULT CPlayerUnder::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CPlayerUnder::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	// For.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_VIBuffer_RectTexture",
		L"Com_VIBuffer",
		(CComponent**)&m_pVIBuffer)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Texture");
		return E_FAIL;
	}

	// For.Com_Texture
	if (FAILED(CGameObject::Add_Component(
		EResourceType::NonStatic,
		L"Component_Texture_PlayerUnder",
		L"Com_Texture",
		(CComponent**)&m_pTexture)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Texture");
		return E_FAIL;
	}


	// For.Com_Transform
	TRANSFORM_DESC TransformDesc;
	TransformDesc.vPosition = _float3(20.f, -5.f, 20.f);
	TransformDesc.vRotate = _float3(0.f, 0.f, 0.f);

	TransformDesc.fSpeedPerSec = 20.f;
	TransformDesc.fRotatePerSec = D3DXToRadian(80.f);
	TransformDesc.vScale = { 20.f, 20.f, 0.f };

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
	m_pPlayerTransform = (CTransform*)m_pManagement->Get_Component(L"Layer_Lobby_Model", L"Com_Transform");
	return S_OK;
}

_uint CPlayerUnder::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);	

	Movement(fDeltaTime);
	
	m_pTransform->Update_Transform();
	return NO_EVENT;
}

_uint CPlayerUnder::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::Alpha, this)))
		return UPDATE_ERROR;
	return _uint();
}

_uint CPlayerUnder::Render_GameObject()
{
	CGameObject::Render_GameObject();
	DWORD dwVal;
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->GetRenderState(D3DRS_ALPHAREF, &dwVal);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 241.f);
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Render_VIBuffer();
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, dwVal);

#ifdef _DEBUG // Render Collide
	
#endif

	return _uint();
}

_uint CPlayerUnder::Movement(_float fDeltaTime)
{
	CCamera* pCam = (CCamera*)m_pManagement->Get_GameObject(L"Layer_Cam");
	_float3 vPos = pCam->Get_CameraDesc().vAt;
	vPos.x += 2.f;
	vPos.y -= 5.f;
	m_pTransform->Set_Position(vPos);
	

	_float3 vRot = { 0,0,-D3DXToRadian(20.f) };
	m_pTransform->Set_Rotate(vRot);
	
	return _uint();
}

CPlayerUnder * CPlayerUnder::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayerUnder* pInstance = new CPlayerUnder(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayerUnder::Clone(void * pArg/* = nullptr*/)
{
	CPlayerUnder* pClone = new CPlayerUnder(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CPlayerUnder::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	
	CGameObject::Free();
}
