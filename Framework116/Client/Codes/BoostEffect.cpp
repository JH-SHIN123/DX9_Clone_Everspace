#include "stdafx.h"
#include "BoostEffect.h"
#include "MainCam.h"

CBoostEffect::CBoostEffect(LPDIRECT3DDEVICE9 pDevice) 
	: CGameObject(pDevice)
{
}

CBoostEffect::CBoostEffect(const CBoostEffect& other)
	: CGameObject(other)
{
}

HRESULT CBoostEffect::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CBoostEffect::Ready_GameObject(void* pArg)
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
		L"Component_Texture_Boost",
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
		(CComponent**)&m_pTransform)))
	{
		PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
		return E_FAIL;
	}





	return S_OK;
}

_uint CBoostEffect::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	// 현재 위치에서 플레이어 방향으로 여러개의 빌보드 발사
	if (m_fSpawnTime <= m_fSpawnDeltaT)
	{
		/* 빌보딩 */
		_float4x4 matView;
		m_pDevice->GetTransform(D3DTS_VIEW, &matView);

		_float4x4 matScale, matRotate, matTrans;
		D3DXMatrixScaling(&matScale, 10.f, 10.f, 10.f);

		D3DXMatrixIdentity(&matRotate);
		memcpy(&matRotate._11, &matView._11, sizeof(_float3));
		memcpy(&matRotate._21, &matView._21, sizeof(_float3));
		memcpy(&matRotate._31, &matView._31, sizeof(_float3));
		D3DXMatrixInverse(&matRotate, 0, &matRotate);

		_float4x4 matRotateY;
		D3DXMatrixRotationY(&matRotateY, 90.f);
		matRotate *= matRotateY;

		//matTrans
		D3DXMatrixIdentity(&matTrans);
		CMainCam* pMainCam = (CMainCam*)m_pManagement->Get_GameObject(L"Layer_Cam");
		if (pMainCam)
			memcpy(&matTrans._41, &pMainCam->Get_CameraDesc().vAt, sizeof(_float3));

		// Build Particle World
		// 위치세팅 (원모양으로)
		for (float fAngle = 0.f; fAngle <= 360.f; fAngle += 360.f / m_iParticleCount)
		{
			_float4x4 matWorld;
			matWorld = matScale * matRotate * matTrans;

			// 원형으로 세팅
			_float3 vRight;
			_float3 vUp;
			_float3 vPos;
			memcpy(&vRight, &matWorld._11, sizeof(_float3));
			memcpy(&vUp, &matWorld._21, sizeof(_float3));
			memcpy(&vPos, &matWorld._41, sizeof(_float3));

			vPos += vRight * m_fCircleRadius * cosf(D3DXToRadian(fAngle));
			vPos += vUp * m_fCircleRadius * sinf(D3DXToRadian(fAngle));
			memcpy(&matWorld._41, &vPos, sizeof(_float3));

			m_pTransform->Set_WorldMatrix(matWorld);

			if (FAILED(m_pManagement->Add_GameObject_InLayer(
				EResourceType::Static,
				L"GameObject_BoostEffectParticle",
				L"Layer_BoostEffectParticle",
				(void*)&m_pTransform->Get_TransformDesc().matWorld)))
			{
				PRINT_LOG(L"Error", L"Failed To Add Boss_Monster In Layer");
				return E_FAIL;
			}
		}

		m_fSpawnDeltaT = 0.f;
	}
	else m_fSpawnDeltaT += fDeltaTime;

	return  _uint();  
}

_uint CBoostEffect::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	//if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::Alpha, this)))
	//	return UPDATE_ERROR;

	return _uint();
}

_uint CBoostEffect::Render_GameObject()
{
	// Render X
	// Particles Render

	//CGameObject::Render_GameObject();

	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
	//m_pTexture->Set_Texture(0);
	//m_pVIBuffer->Render_VIBuffer();

	return _uint();
}

_uint CBoostEffect::IsBillboarding()
{


	return _uint();
}

CBoostEffect* CBoostEffect::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CBoostEffect* pInstance = new CBoostEffect(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBoostEffect::Clone(void* pArg)
{
	CBoostEffect* pClone = new CBoostEffect(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CBoostEffect::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);

	CGameObject::Free();
}
