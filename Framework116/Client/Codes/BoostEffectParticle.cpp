#include "stdafx.h"
#include "BoostEffectParticle.h"

CBoostEffectParticle::CBoostEffectParticle(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CBoostEffectParticle::CBoostEffectParticle(const CBoostEffectParticle& other)
	: CGameObject(other)
{
}

HRESULT CBoostEffectParticle::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CBoostEffectParticle::Ready_GameObject(void* pArg)
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
		L"Component_Texture_Smoke",
		L"Com_Texture",
		(CComponent**)&m_pTexture)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Texture");
		return E_FAIL;
	}

	// For.World
	m_matWorld = *(_float4x4*)pArg;

	//_float4x4 matScale, matRotate;
	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	//D3DXMatrixRotationY(&matRotate, D3DXToRadian(-45.f));
	//m_matWorld *= matScale * matRotate;

	return S_OK;
}

_uint CBoostEffectParticle::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	if (m_fLifeTime <= m_fLifeDeltaT) {
		return DEAD_OBJECT;
	}
	else m_fLifeDeltaT += fDeltaTime;

	// 살짝 y축 회전 후
	// 이펙트 발사(총알처럼)
	_float3 vLook;
	memcpy(&vLook, &m_matWorld._31, sizeof(_float3));
	D3DXVec3Normalize(&vLook, &vLook);

	_float3 vPos;
	memcpy(&vPos, &m_matWorld._41, sizeof(_float3));
	vPos += -vLook * 30.f * fDeltaTime;
	memcpy(&m_matWorld._41, &vPos, sizeof(_float3));

	return _uint();
}

_uint CBoostEffectParticle::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::Particle, this)))
		return UPDATE_ERROR;

	return _uint();
}

_uint CBoostEffectParticle::Render_GameObject()
{
	CGameObject::Render_GameObject();

	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Render_VIBuffer();

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return _uint();
}

CBoostEffectParticle* CBoostEffectParticle::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CBoostEffectParticle* pInstance = new CBoostEffectParticle(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBoostEffectParticle::Clone(void* pArg)
{
	CBoostEffectParticle* pClone = new CBoostEffectParticle(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CBoostEffectParticle::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTexture);

	CGameObject::Free();
}
