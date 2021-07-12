#include "stdafx.h"
#include "HUD_Effect.h"

CHUD_Effect::CHUD_Effect(LPDIRECT3DDEVICE9 pDevice)
	: CUI(pDevice)
{
}

CHUD_Effect::CHUD_Effect(const CHUD_Effect& other)
	: CUI(other)
{
}

HRESULT CHUD_Effect::Ready_GameObject_Prototype()
{
	CUI::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CHUD_Effect::Ready_GameObject(void* pArg)
{
	CUI::Ready_GameObject(pArg);

	if (m_pTransform)
		m_pTransform->Set_Scale({ WINCX, WINCY,0.f });

	return S_OK;
}

_uint CHUD_Effect::Update_GameObject(_float fDeltaTime)
{
	CUI::Update_GameObject(fDeltaTime);

	if (m_IsDead == true)
		return DEAD_OBJECT;

	return NO_EVENT;
}

_uint CHUD_Effect::LateUpdate_GameObject(_float fDeltaTime)
{
	CUI::LateUpdate_GameObject(fDeltaTime);

	return _uint();
}

_uint CHUD_Effect::Render_GameObject()
{
	CUI::Render_GameObject();

	return _uint();
}

CHUD_Effect* CHUD_Effect::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CHUD_Effect* pInstance = new CHUD_Effect(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CHUD_Effect::Clone(void* pArg)
{
	CHUD_Effect* pClone = new CHUD_Effect(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CHUD_Effect::Free()
{
	CUI::Free();

}
