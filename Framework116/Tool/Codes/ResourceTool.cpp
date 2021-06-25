// ../Codes/ResourceTool.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "Tool.h"
#include "../Headers/ResourceTool.h"
#include "afxdialogex.h"



// CResourceTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CResourceTool, CDialog)

CResourceTool::CResourceTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RESOURCETOOL, pParent)
{

}

CResourceTool::~CResourceTool()
{
}

void CResourceTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DROPFILELIST, CDropFileList);
	DDX_Control(pDX, IDC_LIST1, CTextureIndexList);
}

void CResourceTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TCHAR szFileName[MAX_PATH] = L""; //뭐 반환한다 했는지 기억하는게 좋을 것이야. 
	int iSize = DragQueryFile(hDropInfo, -1, nullptr, 0);
	for (auto& pPathInfo : m_ListResource)
		Safe_Delete(pPathInfo);
	m_ListResource.clear();
	for (int i = 0; i < iSize; ++i)
	{
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
		// 여기서 그시기 하면 되겠군. 
		MultiTextureInfo_Extraction(szFileName, m_ListResource);
	}
	CDropFileList.ResetContent();
	for (auto& pPathInfo : m_ListResource)
	{
		TCHAR szDrawID[32] = L"";
		_itow_s(pPathInfo->dwTextureCount, szDrawID, 10);
		TCHAR szType[32] = L"";
		switch (pPathInfo->dwResourceType)
		{
		case (DWORD)EType::CUBE:
			swprintf_s(szType, L"CUBE");
			break;
		case (DWORD)EType::TEXTURE:
			swprintf_s(szType, L"TEXTURE");
			break;
		}
		wstring wstrPathCombine = pPathInfo->wstrFilePath + L"|" + pPathInfo->wstrPrototypeTag + L"|" 
			+ szType + L"|" + szDrawID;
		CDropFileList.AddString(wstrPathCombine.c_str());
	}
	CDropFileList.SetHorizontalExtent(800);
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CResourceTool::MultiTextureInfo_Extraction(const wstring wstrFilePath, list<PASSDATA_RESOURCE*>& listPathInfo)
{
	CFileFind Find;
	wstring wstrNextPath = wstrFilePath + L"\\*.*";

	//FindFile -파일의 존재 유무를 확인하는 함수. 만약 다음 파일에 접근하고 싶다면 !? FindNextFile 함수를 사용해야 한다. 
	// 이 함수는 단순 존재만 확인 가능. 
	BOOL bContinue = Find.FindFile(wstrNextPath.c_str());
	while (bContinue)
	{
		// 다음 파일에 접근할 수 있는 함수. 만약 파일의 끝 (즉 없거나 맨 끝이거나)에 도달하면 !? false, 
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;
		else if (Find.IsDirectory())
			MultiTextureInfo_Extraction(Find.GetFilePath().GetString(), listPathInfo);
		else
		{
			// 내가 진짜 파일을 찾았다 라는 소리가 된다 
			if (Find.IsSystem())
				continue;
			PASSDATA_RESOURCE* pPathInfo = new PASSDATA_RESOURCE;
			TCHAR szFileDirectory[MAX_PATH] = L"";
			//Find. GetFilePath파일의 경로를 반환해주는 함수. 
			//D:\박병건\116A\FrameWork\Texture\Stage\Terrain\Tile\Tile0.png
			lstrcpy(szFileDirectory, Find.GetFilePath().GetString());
			wstring wstrTextureName = szFileDirectory;
			//Tile0
			wstring FileType = PathFindExtension(wstrTextureName.c_str());
			if (L".png" == FileType)
			{
				pPathInfo->dwResourceType = (DWORD)EType::TEXTURE;
			}
			else if (L".dds" == FileType)
			{
				pPathInfo->dwResourceType = (DWORD)EType::CUBE;
			}
			else
				continue;
			PathRemoveFileSpec(szFileDirectory);
			//D:\박병건\116A\FrameWork\Texture\Stage\Terrain\Tile
			pPathInfo->dwTextureCount = MultiTextureCount(szFileDirectory);

			// 경로부터. 
			//Tile0
			//D:\박병건\116A\FrameWork\Texture\Stage\Terrain\Tile\Tile0.png
		
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.length() - 4) + L"%d"+FileType;
			// Tile0 -> Tile%d.png
			
			PathCombine(szFileDirectory, szFileDirectory, wstrTextureName.c_str());
			//D:\박병건\116A\FrameWork\Texture\Stage\Terrain\Tile\Tile%d.png
			pPathInfo->wstrFilePath = ConvertRelativePath(szFileDirectory);
		
			PathRemoveFileSpec(szFileDirectory);
			pPathInfo->wstrPrototypeTag = PathFindFileName(szFileDirectory);
			
			listPathInfo.emplace_back(pPathInfo);
			return;
		}
	}
}

DWORD CResourceTool::MultiTextureCount(const wstring wstrFilePath)
{
		CFileFind Find;
		//D:\박병건\116A\FrameWork\Texture\Stage\Terrain\Tile\*.*
		wstring wstrNextFile = wstrFilePath + L"\\*.*";
		BOOL bContinue = Find.FindFile(wstrNextFile.c_str());
		DWORD iCount = 0;
		while (bContinue)
		{
			bContinue = Find.FindNextFile();
			wstring FileType = PathFindExtension(Find.GetFilePath());
			if (Find.IsSystem() || Find.IsDots())
				continue;
			if (FileType != L".png" && FileType != L".dds")
				continue;
			++iCount;
		}
		return iCount;
}

CString CResourceTool::ConvertRelativePath(const CString & wstrabsPath)
{
		TCHAR szCurrentDir[MAX_PATH] = L"";
		GetCurrentDirectory(MAX_PATH, szCurrentDir);
		TCHAR szRelativePath[MAX_PATH] = L"";
		PathRelativePathTo(szRelativePath, szCurrentDir, FILE_ATTRIBUTE_DIRECTORY, wstrabsPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

		return CString(szRelativePath);
}
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


BEGIN_MESSAGE_MAP(CResourceTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_DROPFILELIST, &CResourceTool::OnLbnSelchangeDropfilelist)
END_MESSAGE_MAP()


// CResourceTool 메시지 처리기입니다.
