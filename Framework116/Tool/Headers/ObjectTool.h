#pragma once

#ifndef __OBJECT_PROTOTYPE_TOOL_H__
#define __OBJECT_PROTOTYPE_TOOL_H__


#include "pch.h"
#include "afxwin.h"
#include "../Headers/MyAddComponent.h" 

// CObjectTool 대화 상자입니다.

class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)

public:
	CObjectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public: // 그냥 함수
	void Setting_List_Box();

public:
	CListBox m_ListBoxObject;	// 오브젝트 프로토 타입 리스트박스
	CListBox m_ListAddedCom;	// 오브젝트 프로토 타입이 가지고 있는 컴포넌트들
	CListBox m_ListComponent;	// 추가 가능한 컴포넌트 목록

	_bool m_bListCheck = false;
	wstring m_ObjectPrototypeTag = L"";
	wstring m_PickedComponentTag = L"";
	//vector

public:
	afx_msg void OnBnClickedButton2(); // Add Component

};

#endif // !__OBJECT_PROTOTYPE_TOOL_H__
