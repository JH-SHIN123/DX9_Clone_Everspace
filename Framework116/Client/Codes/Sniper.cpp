#include "stdafx.h"
#include "..\Headers\Sniper.h"

CSniper::CSniper(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CSniper::CSniper(const CSniper & other)
	: CGameObject(other)
{
}

HRESULT CSniper::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CSniper::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	// For.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_Mesh_Axis",
		L"Com_Mesh",
		(CComponent**)&m_pModelMesh)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_VIBuffer");
		return E_FAIL;
	}

	// For.Com_Transform
	TRANSFORM_DESC TransformDesc;
	TransformDesc.vPosition = _float3(0.5f, 0.f, 0.5f);	
	TransformDesc.vScale = _float3(5.f, 5.f, 5.f);
	TransformDesc.fSpeedPerSec = 40.f;
	TransformDesc.fRotatePerSec = D3DXToRadian(60.f);

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
	BoundingSphere.fRadius = 1.f;

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


	m_pPlayerTransform = (CTransform*)m_pManagement->Get_Component(L"Layer_Player", L"Com_Transform");
	Safe_AddRef(m_pPlayerTransform);

	if (nullptr == m_pPlayerTransform)
	{
		PRINT_LOG(L"Error", L"Player Transform is nullptr");
		return E_FAIL;
	}

	return S_OK;
}

_uint CSniper::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);	
	
	//배틀모드가 아닐때는 그냥 돌아다니렴.
	if (!m_IsBattle)
		Movement(fDeltaTime);
	else
		Sniper_Battle(fDeltaTime);

	m_pTransform->Update_Transform();
	m_pCollide->Update_Collide(m_pTransform->Get_TransformDesc().matWorld);
	return NO_EVENT;
}

_uint CSniper::LateUpdate_GameObject(_float fDeltaTime)
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

_uint CSniper::Render_GameObject()
{
	CGameObject::Render_GameObject();

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	m_pModelMesh->Render_Mesh(); 

#ifdef _DEBUG // Render Collide
	m_pCollide->Render_Collide();
#endif

	return _uint();
}

_uint CSniper::Movement(_float fDeltaTime)
{
	//최초에 가만히 있을래 아니면 돌아다닐래? -> 돌아다니자 ㅋㅋ
	m_pTransform->Go_Straight(fDeltaTime);
	m_pTransform->RotateY(fDeltaTime);

	// 플레이어와의 거리를 계속 계산해서 감지할지 말지 여부를 정함!
	_float3 vPlayerPos = m_pPlayerTransform->Get_State(EState::Position);
	_float3 vSniperPos = m_pTransform->Get_State(EState::Position);

	_float3 vDir = (vPlayerPos - vSniperPos);
	_float vDist = D3DXVec3Length(&vDir);

	// 배틀 상태 On
	if (vDist <= 400.f)
		m_IsBattle = true;

	return _uint();
}


_uint CSniper::Sniper_Battle(_float fDeltaTime)
{
	// 플레이어 쪽으로 회전해! -> OK!
	RotateToPlayer(fDeltaTime);

	// 플레이어쪽을 바라보고 있으면 락온시작! 그게아니면 계속 회전이나 하렴
	if (m_IsLookingPlayer)
		Lock_On(fDeltaTime);
	else
		return _uint();


	return _uint();
}

_uint CSniper::Lock_On(_float fDeltaTime)
{
	// 락온 시작하면 락온 되었다는걸 알리기 위해서 플레이어로 향하는 레이저를 발사해야 할까?..
	// 아니면 플레이어 HUD에서 퉁쳐야하나?
	m_IsLockOn = true;

	m_fSniperShootDelay += fDeltaTime;
	// 락온을 4초동안 한다음에 투사체 하나 발사하자
	if (m_fSniperShootDelay >= 4.f)
	{
		TRANSFORM_DESC* pArg = new TRANSFORM_DESC;

		pArg->vPosition = m_pTransform->Get_State(EState::Position);
		pArg->vRotate = m_pTransform->Get_TransformDesc().vRotate;

		if (FAILED(m_pManagement->Add_GameObject_InLayer(
			EResourceType::NonStatic,
			L"GameObject_Sniper_Bullet",
			L"Layer_Sniper_Bullet", pArg)))
		{
			PRINT_LOG(L"Error", L"Failed To Add GameObject_Sniper_Bullet In Layer");
			return E_FAIL;
		}
		m_fSniperShootDelay = 0.f;
	}

	return _uint();
}


CSniper * CSniper::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CSniper* pInstance = new CSniper(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CSniper");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSniper::Clone(void * pArg/* = nullptr*/)
{
	CSniper* pClone = new CSniper(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CSniper");
		Safe_Release(pClone);
	}

	return pClone;
}

void CSniper::Free()
{
	Safe_Release(m_pModelMesh);
	Safe_Release(m_pPlayerTransform);
	Safe_Release(m_pTransform);
	Safe_Release(m_pCollide);

	CGameObject::Free();
}

_bool CSniper::RotateToPlayer(_float fDeltaTime)
{
	_float3 vTargetPos = m_pPlayerTransform->Get_State(EState::Position);
	_float3 vSniperPos = m_pTransform->Get_State(EState::Position);

	_float3 vTargetDir = vTargetPos - vSniperPos;
	D3DXVec3Normalize(&vTargetDir, &vTargetDir);

	_float3 vSniperLook = m_pTransform->Get_State(EState::Look);
	_float3 vSniperUp = m_pTransform->Get_State(EState::Up);
	D3DXVec3Normalize(&vSniperLook, &vSniperLook);

	_float fCeta = D3DXVec3Dot(&vTargetDir, &vSniperLook);
	_float fRadianMax = D3DXToRadian(95.f);
	_float fRadianMin = D3DXToRadian(85.f);

	_float3 vMyRight, vMyLeft, vMissileUp, vMissileDown;
	D3DXVec3Cross(&vMyRight, &vSniperUp, &vSniperLook);
	D3DXVec3Cross(&vMyLeft, &vSniperLook, &vSniperUp);
	D3DXVec3Cross(&vMissileUp, &vMyRight, &vSniperLook);
	D3DXVec3Cross(&vMissileDown, &vSniperLook, &vMyRight);

	D3DXVec3Normalize(&vMyRight, &vMyRight);
	D3DXVec3Normalize(&vMyLeft, &vMyLeft);
	D3DXVec3Normalize(&vMissileUp, &vMissileUp);
	D3DXVec3Normalize(&vMissileDown, &vMissileDown);

	_float fRight = D3DXVec3Dot(&vTargetDir, &vMyRight);
	_float fLeft = D3DXVec3Dot(&vTargetDir, &vMyLeft);
	_float fUp = D3DXVec3Dot(&vTargetDir, &vMissileUp);
	_float fDown = D3DXVec3Dot(&vTargetDir, &vMissileDown);

	
	if (fRight < fLeft)
		m_pTransform->RotateY(-fDeltaTime);
	else
		m_pTransform->RotateY(fDeltaTime);

	if (fUp < fDown)
		m_pTransform->RotateX(-fDeltaTime);
	else
		m_pTransform->RotateX(fDeltaTime);

	if (fabs(fRight - fLeft) < 10.f || fabs(fUp - fDown) < 10.f)
	{
		m_IsLookingPlayer = true;
	}
	else
		m_IsLookingPlayer = false;

	return m_IsLookingPlayer;
}
