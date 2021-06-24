#pragma once
#include "afxwin.h"


// CResourceTool 대화 상자입니다.

class CResourceTool : public CDialog
{
	DECLARE_DYNAMIC(CResourceTool)

public:
	CResourceTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CResourceTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESOURCETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);

	CListBox CDropFileList;
	CListBox CTextureIndexList;
};
