#include "stdafx.h"
#include "..\Headers\Bullet_EMP_Bomb.h"

CBullet_EMP_Bomb::CBullet_EMP_Bomb(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CBullet_EMP_Bomb::CBullet_EMP_Bomb(const CBullet_EMP_Bomb & other)
	: CGameObject(other)
	, m_fExplosionTime(other.m_fExplosionTime)
	, m_fExplosionRadius(other.m_fExplosionRadius)
	, m_IsExplosion(other.m_IsExplosion)
	, m_IsTracking(other.m_IsTracking)
	, m_fLiveTime(other.m_fLiveTime)
	, m_fTurnTime(other.m_fTurnTime)
	, m_IsMove(other.m_IsMove)
{
}

HRESULT CBullet_EMP_Bomb::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CBullet_EMP_Bomb::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	// For.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(
		EResourceType::Static,
		L"Component_VIBuffer_RectColor",
		L"Com_CubeTexture",
		(CComponent**)&m_pCube)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_CubeTexture");
		return E_FAIL;
	}

	// For.Com_Texture
	if (FAILED(CGameObject::Add_Component(
		EResourceType::NonStatic,
		L"Component_Texture_BossEMP",
		L"Com_Texture",
		(CComponent**)&m_pTexture)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Texture");
		return E_FAIL;
	}

	// For.Com_Transform

	TRANSFORM_DESC TransformDesc;
	TransformDesc.vPosition = ((TRANSFORM_DESC*)pArg)->vPosition;//_float3(10.f, 3.f, 20.f);
	TransformDesc.vRotate = ((TRANSFORM_DESC*)pArg)->vRotate;
	TransformDesc.fSpeedPerSec = 30.f;
	TransformDesc.fRotatePerSec = D3DXToRadian(80.f);
	TransformDesc.vScale = { 1.f, 1.f, 1.f };

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
	// asdasd

	// For.Com_Collide
	BOUNDING_SPHERE BoundingSphere;
	BoundingSphere.fRadius = m_fExplosionRadius;

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

	m_pTargetTransform = (CTransform*)m_pManagement->Get_Component(L"Layer_Player", L"Com_Transform");
	Safe_AddRef(m_pTargetTransform);
	if (nullptr == m_pTargetTransform)
	{
		PRINT_LOG(L"Error", L"m_pTargetTransform is nullptr");
		return E_FAIL;
	}

	//m_pParentTransform = (CTransform*)m_pManagement->Get_Component(L"GameObject_Boss_Monster", L"Com_Transform");
	//Safe_AddRef(m_pParentTransform);
	//if (nullptr == m_pParentTransform)
	//{
	//	PRINT_LOG(L"Error", L"m_pParentTransform is nullptr");
	//	return E_FAIL;
	//}



	return S_OK;
}

_uint CBullet_EMP_Bomb::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	Turn(fDeltaTime);

	m_pTransform->Go_Straight(fDeltaTime);

	//Movement(fDeltaTime);

	m_pTransform->Update_Transform();
	m_pCollide->Update_Collide(m_pTransform->Get_TransformDesc().matWorld);
	return NO_EVENT;
}

_uint CBullet_EMP_Bomb::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::NonAlpha, this)))
		return UPDATE_ERROR;


	m_fLiveTime -= fDeltaTime;
	if (m_fLiveTime <= 0.f)
		return DEAD_OBJECT;


	return _uint();
}

_uint CBullet_EMP_Bomb::Render_GameObject()
{
	CGameObject::Render_GameObject();

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	m_pTexture->Set_Texture(0);
	m_pCube->Render_VIBuffer();

#ifdef _DEBUG // Render Collide
	//m_pCollide->Render_Collide();
#endif

	return _uint();
}

_uint CBullet_EMP_Bomb::Turn(_float fDeltaTime)
{
	m_IsMove = true;

	if (m_fTurnTime >= 0.f)
	{
		m_IsMove = false;
		m_fTurnTime -= fDeltaTime;
		m_pTransform->RotateX(fDeltaTime);
	}

	return _uint();
}

_uint CBullet_EMP_Bomb::Movement(_float fDeltaTime)
{
	Homing(fDeltaTime);

	// Rotate 로 회전하며 다가오게 하자
	Move_Rotate(fDeltaTime);


	// Boom
	if (m_fExplosionTime <= 0.f)
	{
		if (m_fExplosionRadius <= 1.05f)
		{
			m_IsExplosion = true;
			m_fExplosionRadius *= 1.0015f;
			m_pCollide->Resize_Shpere(m_fExplosionRadius);
		}
	}

	else
		m_fExplosionTime -= fDeltaTime;




	return _uint();
}

_uint CBullet_EMP_Bomb::Homing(_float fDeltaTime)
{
	if (m_IsMove == false)
		return 0;

	if (m_IsExplosion == false)
	{
		m_pTransform->Update_Transform();

		_float3 vTargetPos = m_pTargetTransform->Get_State(EState::Position);
		_float3 vMyPos = m_pTransform->Get_State(EState::Position);
		m_vHomingDir = vTargetPos - vMyPos;
		//D3DXVec3Normalize(&m_vMoveDir, &m_vMoveDir);

		//m_pTransform->Go_Dir(m_vMoveDir, fDeltaTime);

	//	m_IsTracking = true;
	}

	return _uint();
}

_uint CBullet_EMP_Bomb::Move_Rotate(_float fDeltaTime)
{
	// 난 플레이어의 방향을 알아

	if (m_IsMove == false &&
		m_IsExplosion == true)
		return 0;

	Rotate_X(fDeltaTime);
	Rotate_Y(fDeltaTime);

	m_pTransform->Go_Straight(fDeltaTime);


	return _uint();
}

_uint CBullet_EMP_Bomb::Rotate_X(_float fDeltaTime)
{
	_float3 vTargetPos = m_pTargetTransform->Get_State(EState::Position);
	_float3 vMyPos = m_pTransform->Get_State(EState::Position);

	_float3 vTargetDir = vTargetPos - vMyPos;

	_float3 vMyLook = m_pTransform->Get_State(EState::Look);
	_float3 vMyRight = m_pTransform->Get_State(EState::Right);

	_float3 vMyUp, vMyDown;
	D3DXVec3Cross(&vMyUp, &vMyLook, &vMyRight);
	D3DXVec3Cross(&vMyDown, &vMyRight, &vMyLook);

	D3DXVec3Normalize(&vMyUp, &vMyUp);
	D3DXVec3Normalize(&vMyDown, &vMyDown);

	_float fUpScala = D3DXVec3Dot(&vTargetDir, &vMyUp);
	_float fDownScala = D3DXVec3Dot(&vTargetDir, &vMyDown);

	_float fCeta = D3DXVec3Dot(&vTargetDir, &vMyLook);
	_float fRadianMax = D3DXToRadian(95.f);
	_float fRadianMin = D3DXToRadian(85.f);


	if (fUpScala < fDownScala)
		m_pTransform->RotateX(fDeltaTime);

	else
		m_pTransform->RotateX(-fDeltaTime);

	return _uint();
}

_uint CBullet_EMP_Bomb::Rotate_Y(_float fDeltaTime)
{
	_float3 vTargetPos = m_pTargetTransform->Get_State(EState::Position);
	_float3 vMyPos = m_pTransform->Get_State(EState::Position);

	_float3 vTargetDir = vTargetPos - vMyPos;
	D3DXVec3Normalize(&vTargetDir, &vTargetDir);

	_float3 vMyLook = m_pTransform->Get_State(EState::Look);
	_float3 vMyUp = m_pTransform->Get_State(EState::Up);
	D3DXVec3Normalize(&vMyLook, &vMyLook);

	_float fCeta = D3DXVec3Dot(&vTargetDir, &vMyLook);
	_float fRadianMax = D3DXToRadian(95.f);
	_float fRadianMin = D3DXToRadian(85.f);

	_float3 vMyRight, vMyLeft;
	D3DXVec3Cross(&vMyRight, &vMyUp, &vMyLook);
	D3DXVec3Cross(&vMyLeft, &vMyLook, &vMyUp);

	D3DXVec3Normalize(&vMyRight, &vMyRight);
	D3DXVec3Normalize(&vMyLeft, &vMyLeft);

	_float fRight = D3DXVec3Dot(&vTargetDir, &vMyRight);
	_float fLeft = D3DXVec3Dot(&vTargetDir, &vMyLeft);

	//if (fCeta < fRadianMin)
	//{
	if (fRight < fLeft)
		m_pTransform->RotateY(-fDeltaTime);

	else
		m_pTransform->RotateY(fDeltaTime);

	return _uint();
}

CBullet_EMP_Bomb * CBullet_EMP_Bomb::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CBullet_EMP_Bomb* pInstance = new CBullet_EMP_Bomb(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Boss_Monster");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBullet_EMP_Bomb::Clone(void * pArg/* = nullptr*/)
{
	CBullet_EMP_Bomb* pClone = new CBullet_EMP_Bomb(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Boss_Monster");
		Safe_Release(pClone);
	}

	return pClone;
}

void CBullet_EMP_Bomb::Free()
{
	Safe_Release(m_pTargetTransform);

	Safe_Release(m_pCube);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pCollide);

	CGameObject::Free();
}
