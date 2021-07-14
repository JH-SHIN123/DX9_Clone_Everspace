#include "stdafx.h"
#include "..\Headers\Monster.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CMonster::CMonster(const CMonster & other)
	: CGameObject(other)
{
}

HRESULT CMonster::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CMonster::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	// For.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_Mesh_Enemy1",
		L"Com_Mesh",
		(CComponent**)&m_pModelMesh)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_VIBuffer");
		return E_FAIL;
	}

	// For.Com_Transform
	TRANSFORM_DESC TransformDesc;
	TransformDesc.vPosition = _float3(150.f, 0.f, 150.f);	
	TransformDesc.vScale = _float3(20.f, 20.f, 20.f);
	TransformDesc.fSpeedPerSec = 30.f;
	TransformDesc.fRotatePerSec = D3DXToRadian(45.f);

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

	// For.Com_Collide
	BOUNDING_SPHERE BoundingSphere;
	BoundingSphere.fRadius = 6.f;

	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_CollideSphere",
		L"Com_CollideSphere",
		(CComponent**)&m_pCollide,
		&BoundingSphere,
		true)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
		return E_FAIL;
	}

	// Init
	m_vCreatePosition = TransformDesc.vPosition;
	m_vResearchRange = { 50.f,50.f,50.f };

	m_pTargetTransform = (CTransform*)m_pManagement->Get_Component(L"Layer_Player", L"Com_Transform");
	if (nullptr == m_pTargetTransform)
	{
		PRINT_LOG(L"Error", L"m_pTargetTransform is nullptr");
		return E_FAIL;
	}

	return S_OK;
}

_uint CMonster::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);	
	
	Search_Target(fDeltaTime);

	if(!m_bBattle)
		Movement(fDeltaTime);
	else
		
		

	m_pTransform->Update_Transform();
	m_pCollide->Update_Collide(m_pTransform->Get_TransformDesc().matWorld);
	return NO_EVENT;
}

_uint CMonster::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::NonAlpha, this)))
		return UPDATE_ERROR;

	if (m_IsCollide) {
		CEffectHandler::Add_Layer_Effect_Explosion(m_pTransform->Get_State(EState::Position), 1.f);
		m_IsCollide = false;
	}

	return _uint();
}

_uint CMonster::Render_GameObject()
{
	CGameObject::Render_GameObject();

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	m_pModelMesh->Render_Mesh(); 
	// Test

#ifdef _DEBUG // Render Collide
	m_pCollide->Render_Collide();
#endif

	return _uint();
}

_uint CMonster::Movement(_float fDeltaTime)
{
	// 그냥 와리가리하면서 정찰
	m_fMoveDist += fDeltaTime;

	if (m_fMoveDist > 0.f && m_fMoveDist < 6.f)
	{
		m_pTransform->Go_Straight(fDeltaTime);
	}
	else if (m_fMoveDist >= 6.f && m_fMoveDist < 10.f)
	{
		m_pTransform->RotateY(fDeltaTime);
		
	}
	else if (m_fMoveDist >= 10.f)
	{
		m_fMoveDist = 0.f;
	}
	
	return _uint();
}

_uint CMonster::Search_Target(_float fDeltaTime)
{
	_float3 vTargetPos = m_pTargetTransform->Get_State(EState::Position);
	_float3 vMonsterPos = m_pTransform->Get_State(EState::Position);

	_float3 vDir = vTargetPos - vMonsterPos;
	_float fDist = D3DXVec3Length(&vDir);

		// 배틀상태 On
	if (fDist <= 50.f && fDist != 0.f)
	{
		m_bBattle = true;
	}
	return _uint();
}


CMonster * CMonster::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CMonster* pInstance = new CMonster(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMonster::Clone(void * pArg/* = nullptr*/)
{
	CMonster* pClone = new CMonster(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CMonster::Free()
{
	Safe_Release(m_pModelMesh);
	Safe_Release(m_pTransform);
	Safe_Release(m_pCollide);

	CGameObject::Free();
}
