#pragma once


// CCollideTool 대화 상자

class CCollideTool : public CDialog
{
	DECLARE_DYNAMIC(CCollideTool)

public:
	CCollideTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCollideTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCollideTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
