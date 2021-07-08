#include "stdafx.h"
#include "..\Headers\MissionUI.h"
#include "Collision.h"
#include "Pipeline.h"
#include "Ring.h"

CMissionUI::CMissionUI(LPDIRECT3DDEVICE9 pDevice)
	: CUI(pDevice)
{
}

CMissionUI::CMissionUI(const CMissionUI & other)
	: CUI(other)
{
}

HRESULT CMissionUI::Ready_GameObject_Prototype()
{
	CUI::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CMissionUI::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CUI::Ready_GameObject(pArg);



	return S_OK;
}

_uint CMissionUI::Update_GameObject(_float fDeltaTime)
{
	CUI::Update_GameObject(fDeltaTime);
	
	Movement(fDeltaTime);	
	
	return m_pTransform->Update_Transform();
}

_uint CMissionUI::LateUpdate_GameObject(_float fDeltaTime)
{
	CUI::LateUpdate_GameObject(fDeltaTime);
	
	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::Alpha, this)))
		return UPDATE_ERROR;

	return _uint();
}

_uint CMissionUI::Render_GameObject()
{
	CUI::Render_GameObject();

	//m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	//m_pTexture->Set_Texture(0);
	//m_pVIBuffer->Render_VIBuffer();
	//m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return _uint();
}

_uint CMissionUI::Movement(_float fDeltaTime)
{
	return _uint();
}

_uint CMissionUI::Search_Target(_float fDeltaTime)
{
	return _uint();
}

_uint CMissionUI::BillBorad(_float fDeltaTime)
{
	return _uint();
}

CMissionUI * CMissionUI::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CMissionUI* pInstance = new CMissionUI(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create TutorialUI");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMissionUI::Clone(void * pArg/* = nullptr*/)
{
	CMissionUI* pClone = new CMissionUI(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone TutorialUI");
		Safe_Release(pClone);
	}

	return pClone;
}

void CMissionUI::Free()
{
	CUI::Free();
}
