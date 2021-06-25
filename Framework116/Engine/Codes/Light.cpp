#include "Light.h"
#include "Transform.h"

USING(Engine)

CLight::CLight(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CLight::CLight(const CLight& other)
	: CGameObject(other)
{
}

HRESULT CLight::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CLight::Ready_GameObject(void* pArg)
{
	CGameObject::Ready_GameObject(pArg);

	return S_OK;
}

_uint CLight::Update_GameObject(_float fDeltaTime)
{

	return _uint();
}

_uint CLight::LateUpdate_GameObject(_float fDeltaTime)
{
	return _uint();
}

_uint CLight::Render_GameObject()
{
	return _uint();
}

CLight* CLight::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return nullptr;
}

CGameObject* CLight::Clone(void* pArg)
{
	return nullptr;
}

void CLight::Free()
{
}
