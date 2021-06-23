#pragma once

#ifndef __MYADDCOMPONENT_H__
#define __MYADDCOMPONENT_H__


#include "pch.h"
#include "afxwin.h"
#include "ObjectTool.h"

// CMyAddComponent 대화 상자입니다.

class CMyAddComponent : public CDialog
{
	DECLARE_DYNAMIC(CMyAddComponent)

public:
	CMyAddComponent(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMyAddComponent();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYADDCOMPONENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


public:
	_bool m_bListCheck = false;
	CListBox m_ListAddCom;
	CString m_wstrPickComponent;

public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton1();
};


#endif // !__MYADDCOMPONENT_H__
