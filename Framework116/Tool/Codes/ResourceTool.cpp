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
	//TCHAR szFileName[MAX_PATH] = L""; //뭐 반환한다 했는지 기억하는게 좋을 것이야. 
	//int iSize = DragQueryFile(hDropInfo, -1, nullptr, 0);
	//// 리스트안에 데이터 있으면 다 지우고 새로 하겠다 라는 뜻아니냐? 
	//// 그럼 다 지워 준다 라는 코드 삽입 ㄱㄱ 
	//for (int i = 0; i < iSize; ++i)
	//{
	//	DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
	//	// 여기서 그시기 하면 되겠군. 
	//	CFileInfo::MultiTextureInfo_Extraction(szFileName, m_listPathInfo);
	//}
	//m_ListBox.ResetContent();
	//for (auto& pPathInfo : m_listPathInfo)
	//{
	//	TCHAR szDrawID[32] = L"";
	//	_itow_s(pPathInfo->iDrawID, szDrawID, 10);
	//	wstring wstrPathCombine = pPathInfo->wstrFilePath + L"|" + pPathInfo->wstrObjectKey + L"|" + pPathInfo->wstrStateKey + L"|" + szDrawID;
	//	m_ListBox.AddString(wstrPathCombine.c_str());
	//}
	//m_ListBox.SetHorizontalExtent(800);
	//UpdateData(FALSE);
	//CDialog::OnDropFiles(hDropInfo);
}


BEGIN_MESSAGE_MAP(CResourceTool, CDialog)
END_MESSAGE_MAP()


// CResourceTool 메시지 처리기입니다.
