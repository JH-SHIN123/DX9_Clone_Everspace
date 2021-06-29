// ../Codes/MeshTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "../Headers/MeshTool.h"
#include "afxdialogex.h"


// CMeshTool 대화 상자

IMPLEMENT_DYNAMIC(CMeshTool, CDialog)

CMeshTool::CMeshTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CMeshTool, pParent)
{

}

CMeshTool::~CMeshTool()
{
}

void CMeshTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMeshTool, CDialog)
END_MESSAGE_MAP()


// CMeshTool 메시지 처리기
