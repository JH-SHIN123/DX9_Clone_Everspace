// ../Codes/ObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "pch.h"
#include "Tool.h"
#include "../Headers/ObjectTool.h"
#include "afxdialogex.h"
//#include "MyAddComponent.h"




// CObjectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectTool, CDialog)

CObjectTool::CObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
{

}

CObjectTool::~CObjectTool()
{
}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBoxObject);
	DDX_Control(pDX, IDC_LIST2, m_ListAddedCom);
	DDX_Control(pDX, IDC_LIST3, m_ListComponent);

	Setting_List_Box();


}

void CObjectTool::Setting_List_Box()
{
	if (m_bListCheck == true)
		return;
	
	// 오브젝트 목록
	m_ListBoxObject.InsertString(0, L"Player");
	m_ListBoxObject.InsertString(1, L"Monster_Normal");
	m_ListBoxObject.InsertString(2, L"Monster_Sniper");
	m_ListBoxObject.InsertString(3, L"Monster_stealth");
	m_ListBoxObject.InsertString(4, L"Monster_Buff");
	m_ListBoxObject.InsertString(5, L"Monster_Boss");





	// 추가 가능한 컴포넌트 목록
	m_ListComponent.InsertString(0, L"VIBuffer_TriColor");
	m_ListComponent.InsertString(1, L"VIBuffer_RectColor");
	m_ListComponent.InsertString(2, L"VIBuffer_RectTexture");
	m_ListComponent.InsertString(3, L"VIBuffer_TerrainColor");
	m_ListComponent.InsertString(4, L"VIBuffer_TerrainTexture");
	m_ListComponent.InsertString(5, L"VIBuffer_CubeTexture");
	m_ListComponent.InsertString(6, L"Transform");
	m_ListComponent.InsertString(7, L"Texture");
	m_ListComponent.InsertString(8, L"Mesh");





	m_bListCheck = true;
	
}


BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CObjectTool::OnBnClickedButton2)
END_MESSAGE_MAP()


// CObjectTool 메시지 처리기입니다.
void CObjectTool::OnBnClickedButton2()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//if (nullptr == (*m_MyAddComponent).GetSafeHwnd())
	//	(*m_MyAddComponent).Create(IDD_MYADDCOMPONENT);
	//(*m_MyAddComponent).ShowWindow(SW_SHOW);



}
