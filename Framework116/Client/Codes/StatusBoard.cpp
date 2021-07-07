#include "stdafx.h"
#include "..\Headers\StatusBoard.h"
#include"Pipeline.h"
#include"LobbyCam.h"
#include"Lobby.h"
CStatusBoard::CStatusBoard(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CStatusBoard::CStatusBoard(const CStatusBoard & other)
	: CGameObject(other)
{
}

HRESULT CStatusBoard::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CStatusBoard::Ready_GameObject(void * pArg/* = nullptr*/)
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
	//For.Com_HexagonVIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::NonStatic,
		L"Component_VIBuffer_HexagonColor",
		L"Com_HexagonVIBuffer",
		(CComponent**)&m_pHexagonBuffer)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_VIBuffer");
		return E_FAIL;
	}
	
	// For.Com_Texture
	if (FAILED(CGameObject::Add_Component(
		EResourceType::NonStatic,
		L"Component_Texture_StatusBoard",
		L"Com_Texture",
		(CComponent**)&m_pTexture)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Texture");
		return E_FAIL;
	}

	TRANSFORM_DESC tTrans;
	tTrans.vScale = { 400.f,400.f,0.f };
	tTrans.vPosition = _float3(-700.f, -200.f, 0.f);
	// For.Com_Transform
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_Transform",
		L"Com_Transform",
		(CComponent**)&m_pTransform,
		&tTrans)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
		return E_FAIL;
	}


	return S_OK;
}

_uint CStatusBoard::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);	
	Movement(fDeltaTime);	
	
	return m_pTransform->Update_Transform();
	
}

_uint CStatusBoard::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);


	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::AlphaUI, this)))
		return UPDATE_ERROR;

	
	return _uint();
}

_uint CStatusBoard::Render_GameObject()
{
	if (m_pLobby->Get_IsGatcha())
		return 0;
	

	CGameObject::Render_GameObject();
	TRANSFORM_DESC transformDesc = m_pTransform->Get_TransformDesc();

	_float4x4 matView;
	D3DXMatrixIdentity(&matView);
	matView._11 = transformDesc.vScale.x;
	matView._22 = transformDesc.vScale.y;
	matView._41 = transformDesc.vPosition.x;
	matView._42 = transformDesc.vPosition.y;
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
	/////////////////////////////////////////////////////////////////
	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Render_VIBuffer();

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pHexagonBuffer->Render_VIBuffer();
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	return _uint();
}

_uint CStatusBoard::Movement(_float fDeltaTime)
{
	return _uint();
}



CStatusBoard * CStatusBoard::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CStatusBoard* pInstance = new CStatusBoard(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CStatusBoard::Clone(void * pArg/* = nullptr*/)
{
	CStatusBoard* pClone = new CStatusBoard(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CStatusBoard::Free()
{

	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pLobby);
	CGameObject::Free();
}
