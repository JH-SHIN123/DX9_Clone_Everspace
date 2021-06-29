#pragma once


// CMeshTool 대화 상자

class CMeshTool : public CDialog
{
	DECLARE_DYNAMIC(CMeshTool)

public:
	CMeshTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMeshTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMeshTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
