// ../Codes/UiTool.cpp : 구현 파일입니다.
//

#include"pch.h"
#include "stdafx.h"
#include "Tool.h"
#include "../Headers/UiTool.h"
#include "afxdialogex.h"

// CUiTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUiTool, CDialog)

CUiTool::CUiTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UITOOL, pParent)
{
}

CUiTool::~CUiTool()
{
}

void CUiTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, CTextureList);
}

void CUiTool::OnLbnSelchangeTextureList()
{
}

void CUiTool::OnBnClickedLoadButton()
{
	if (m_pListResource->size())
	{
		for (auto& pDst : *m_pListResource)
			{
				for (int i = 0; i < pDst->dwTextureCount; i++)
				{
				wstring strTextureProtoTypeTag = pDst->wstrPrototypeTag;
				strTextureProtoTypeTag += L"%d";
				switch (pDst->dwResourceType)
				{
				case (DWORD)ETextureType::SINGLE:
					strTextureProtoTypeTag += L".png";
					break;
				case (DWORD)ETextureType::MULTI:
					strTextureProtoTypeTag += L".png";
					break;	
				case (DWORD)ETextureType::Cube:
					strTextureProtoTypeTag += L".dds";
						break;
				}
				TCHAR szTag[MAX_PATH] = L"";
				swprintf_s(szTag, strTextureProtoTypeTag.c_str(), i);
				CTextureList.AddString(szTag);
			}
		}
	}

}


BEGIN_MESSAGE_MAP(CUiTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUiTool::OnLbnSelchangeTextureList)
	ON_BN_CLICKED(IDC_BUTTON1, &CUiTool::OnBnClickedLoadButton)
END_MESSAGE_MAP()


// CUiTool 메시지 처리기입니다.
