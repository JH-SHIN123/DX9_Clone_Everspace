#include"stdafx.h"
#include "LobbyUI.h"
#include "Transform.h"
#include "Management.h"

USING(Engine)

CLobbyUI::CLobbyUI(LPDIRECT3DDEVICE9 pDevice)
	: CUI(pDevice)
{
}

CLobbyUI::CLobbyUI(const CLobbyUI& other)
	: CUI(other)
{
}

HRESULT CLobbyUI::Ready_GameObject_Prototype()
{
	CUI::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CLobbyUI::Ready_GameObject(void* pArg)
{
	CUI::Ready_GameObject(pArg);
	
	return S_OK;
}

_uint CLobbyUI::Update_GameObject(_float fDeltaTime)
{
	CUI::Update_GameObject(fDeltaTime);
	Update_Bounds();
	// Picking Check
	
	return NO_EVENT;
}

_uint CLobbyUI::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::UI, this)))
		return UPDATE_ERROR;



	return _uint();
}

_uint CLobbyUI::Render_GameObject()
{
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
	m_pTexture->Set_Texture(m_dwIdx);
	m_pVIBuffer->Render_VIBuffer();
	/////////////////////////////////////////////////////////////////

	Set_Text();

	return _uint();
}

void CLobbyUI::Update_Bounds()
{
	
	
	_float3 vPos = _float3(0.f,0.f,0.f);
	_float3 vDecartPos = m_pTransform->Get_TransformDesc().vPosition;

	vPos.x = vDecartPos.x + _float(WINCX/2.f);
	vPos.y = _float(WINCY/2.f)- vDecartPos.y;
	
	_float3 vSize = m_pTransform->Get_TransformDesc().vScale;

	m_tUIBounds.left = vPos.x - (vSize.x/2.f);
	m_tUIBounds.top = vPos.y - (vSize.y/2.f);
	m_tUIBounds.right = vPos.x + (vSize.x/2.f);
	m_tUIBounds.bottom = vPos.y + (vSize.y/2.f);
	
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	m_dwIdx = 0;
	if (PtInRect(&m_tUIBounds, pt))
	{
		if (m_wstrTexturePrototypeTag == L"Component_Texture_RepairIcon")
		{
			int  i = 0;
		}
		if (m_wstrTexturePrototypeTag == L"Component_Texture_ShopIcon")
		{
			int  i = 0;
		}
		if (m_wstrTexturePrototypeTag == L"Component_Texture_PlaneTemplete")
		{
			int  i = 0;
		}

		if (m_wstrTexturePrototypeTag == L"Component_Texture_achievement")
		{
			m_dwIdx = 1;
		}
		if (m_wstrTexturePrototypeTag == L"Component_Texture_everspace_logo")
		{
				int  i = 0;
		}

	}
}

void CLobbyUI::Set_Text()
{
	wstring str;
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (L"Component_Texture_achievement" == m_wstrTexturePrototypeTag)
	{
		str = L"스테이지 진입!";
		rc.left = (WINCX>>1) + 500;
		rc.top = (WINCY >> 1) + 200;
		m_pManagement->Get_Font()->DrawText(NULL
		, str.c_str(), -1
		, &rc, DT_LEFT | DT_TOP, D3DXCOLOR(255, 0, 0, 255));

	}
}

CLobbyUI* CLobbyUI::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLobbyUI* pInstance = new CLobbyUI(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CLobbyUI::Clone(void* pArg)
{
	CLobbyUI* pClone = new CLobbyUI(*this); /* 복사 생성자 호출 */
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CLobbyUI::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);

	CGameObject::Free();
}
