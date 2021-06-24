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
}


BEGIN_MESSAGE_MAP(CResourceTool, CDialog)
END_MESSAGE_MAP()


// CResourceTool 메시지 처리기입니다.
