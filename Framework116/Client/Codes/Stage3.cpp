#include "stdafx.h"
#include "Stage3.h"

CStage3::CStage3(LPDIRECT3DDEVICE9 pDevice)
	: CScene(pDevice)
{
}

HRESULT CStage3::Ready_Scene()
{
	CScene::Ready_Scene();
	::SetWindowText(g_hWnd, L"CStage2");

	//if (FAILED(Add_Layer_Cam(L"Layer_Cam")))
	//	return E_FAIL;

	return S_OK;
}

_uint CStage3::Update_Scene(_float fDeltaTime)
{
	CScene::Update_Scene(fDeltaTime);


	return _uint();
}

_uint CStage3::LateUpdate_Scene(_float fDeltaTime)
{
	CScene::LateUpdate_Scene(fDeltaTime);

	return _uint();
}

CStage3* CStage3::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
	{
		PRINT_LOG(L"Error", L"Device is nullptr");
		return nullptr;
	}

	CStage3* pInstance = new CStage3(pDevice);
	if (FAILED(pInstance->Ready_Scene()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Stage");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStage3::Free()
{
	CScene::Free(); // 2.何葛 府家胶 沥府	
}
