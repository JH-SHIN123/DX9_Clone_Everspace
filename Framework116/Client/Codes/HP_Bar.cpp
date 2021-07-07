#include "stdafx.h"
#include "..\Headers\HP_Bar.h"
#include "Pipeline.h"
#include "Collision.h"

CHP_Bar::CHP_Bar(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CHP_Bar::CHP_Bar(const CHP_Bar & other)
	: CGameObject(other)
{
}

HRESULT CHP_Bar::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CHP_Bar::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	// For.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_VIBuffer_RectTexture_HP_Bar",
		L"Com_VIBuffer",
		(CComponent**)&m_pVIBuffer)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_VIBuffer");
		return E_FAIL;
	}

	// For.Com_Texture
	if (FAILED(CGameObject::Add_Component(
		EResourceType::NonStatic,
		L"Component_Texture_HP_Bar",
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
		(CComponent**)&m_pTransform, pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
		return E_FAIL;
	}

	m_pTargetObject = (CGameObject*)pArg;

	return S_OK;
}

_uint CHP_Bar::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);	

	return m_pTransform->Update_Transform();
}

_uint CHP_Bar::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::UI, this)))
		return UPDATE_ERROR;

	return _uint();
}

_uint CHP_Bar::Render_GameObject()
{
   	CGameObject::Render_GameObject();	

	m_pTargetCollide = m_pTargetObject->Get_Collides()->front();
	
	_float3 TargetCollidePos = m_pTargetCollide->Get_BoundingSphere().Get_Position();

	D3DVIEWPORT9 vp2;
	m_pDevice->GetViewport(&vp2);
	_float4x4 TestView2, TestProj2;
	m_pDevice->GetTransform(D3DTS_VIEW, &TestView2);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &TestProj2);
	_float4x4 matCombine2 = TestView2 * TestProj2;
	D3DXVec3TransformCoord(&TargetCollidePos, &TargetCollidePos, &matCombine2);
	TargetCollidePos.x += 1.f;
	TargetCollidePos.y += 1.f;

	TargetCollidePos.x = (vp2.Width * (TargetCollidePos.x)) / 2.f + vp2.X;
	TargetCollidePos.y = (vp2.Height * (2.f - TargetCollidePos.y) / 2.f + vp2.Y);

	_float3 ptTargetPos;
	ptTargetPos.x = -1.f * (WINCX / 2) + TargetCollidePos.x;
	ptTargetPos.y = 1.f * (WINCY / 2) + TargetCollidePos.y;
	ptTargetPos.z = 0.f;
	
	m_pTransform->Set_Position(ptTargetPos);
	//_float4x4 matView;
	//D3DXMatrixIdentity(&matView);
	//matView._11 = 350.f;
	//matView._22 = 350.f;
	//matView._41 = (_float)ptTargetPos.x;
	//matView._42 = (_float)ptTargetPos.y;

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_pDevice->SetTransform(D3DTS_WORLD, &matView);
	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Render_VIBuffer();
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return _uint();
}

_uint CHP_Bar::Movement(_float fDeltaTime)
{
	return _uint();
}

CHP_Bar * CHP_Bar::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CHP_Bar* pInstance = new CHP_Bar(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create HP_Bar");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CHP_Bar::Clone(void * pArg/* = nullptr*/)
{
	CHP_Bar* pClone = new CHP_Bar(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone HP_Bar");
		Safe_Release(pClone);
	}

	return pClone;
}

void CHP_Bar::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);

	CGameObject::Free();
}

