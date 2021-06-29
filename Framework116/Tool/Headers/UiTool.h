#pragma once
#include "afxwin.h"


// CUiTool 대화 상자입니다.

class CUiTool : public CDialog
{
	DECLARE_DYNAMIC(CUiTool)

public:
	CUiTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUiTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UITOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox CTextureList;
	afx_msg void OnLbnSelchangeTextureList();
	list<PASSDATA_RESOURCE*>* m_pListResource;

	afx_msg void OnBnClickedLoadButton();
};
