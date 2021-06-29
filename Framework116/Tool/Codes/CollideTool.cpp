// ../Codes/CollideTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "../Headers/CollideTool.h"
#include "afxdialogex.h"


// CCollideTool 대화 상자

IMPLEMENT_DYNAMIC(CCollideTool, CDialog)

CCollideTool::CCollideTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CCollideTool, pParent)
{

}

CCollideTool::~CCollideTool()
{
}

void CCollideTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCollideTool, CDialog)
END_MESSAGE_MAP()


// CCollideTool 메시지 처리기
