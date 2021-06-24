// ../Codes/MyAddComponent.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "pch.h"
#include "Tool.h"
#include "../Headers/MyAddComponent.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "MainView.h"
#include "MainForm.h"
#include "framework.h"


// CMyAddComponent 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyAddComponent, CDialog)

CMyAddComponent::CMyAddComponent(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MYADDCOMPONENT, pParent)
{

}

CMyAddComponent::~CMyAddComponent()
{
}

void CMyAddComponent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListAddCom);

	if (m_bListCheck == false)
	{
		m_ListAddCom.InsertString(0, L"VIBuffer_TriColor");
		m_ListAddCom.InsertString(1, L"VIBuffer_RectColor");
		m_ListAddCom.InsertString(2, L"VIBuffer_RectTexture");
		m_ListAddCom.InsertString(3, L"VIBuffer_TerrainColor");
		m_ListAddCom.InsertString(4, L"VIBuffer_TerrainTexture");
		m_ListAddCom.InsertString(5, L"VIBuffer_CubeTexture");
		m_ListAddCom.InsertString(6, L"Transform");
		m_ListAddCom.InsertString(7, L"Texture");
		m_ListAddCom.InsertString(8, L"Mesh");

		m_bListCheck = true;
	}

	/*
	


	*/
}


BEGIN_MESSAGE_MAP(CMyAddComponent, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMyAddComponent::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyAddComponent::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyAddComponent 메시지 처리기입니다.

void CMyAddComponent::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData(TRUE);

	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMainView* pView = dynamic_cast<CMainView*>(pMain->m_tMainSplitterWnd.GetPane(0, 1));

	_int iIndex = m_ListAddCom.GetCurSel();

	CString wstrComponentTag = L"";
	m_ListAddCom.GetText(iIndex, wstrComponentTag);
	m_wstrPickComponent = L"Component_" +  wstrComponentTag;



	//UpdateData(FALSE);
}


void CMyAddComponent::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMainForm* pForm = dynamic_cast<CMainForm*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	//pForm.m_
}



