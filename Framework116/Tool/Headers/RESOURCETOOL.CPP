#include "pch.h"
#include "ResourceTool.h"


void CResourceTool::OnLbnSelchangeDropfilelist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int iSelect = CDropFileList.GetCurSel();

	CString strFileName = L"";
	CDropFileList.GetText(iSelect, strFileName);
	int i = 0;
	for (; i < strFileName.GetLength(); ++i)
	{
		if (isdigit(strFileName[i]))
			break;
	}
	strFileName.Delete(0, i);
	m_dwDrawID = _ttoi(strFileName.GetString());

	CGraphic_Device::Get_Instance()->Render_Begin();
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_dwDrawID);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;
	float fRatioX = g_iWinCX / TILECX;
	float fRatioY = g_iWinCY / TILECY;
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 0.f);
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
	matScale *= matTrans;


	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matScale);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphic_Device::Get_Instance()->Render_End(m_Picture.m_hWnd);
	UpdateData(FALSE);
}
