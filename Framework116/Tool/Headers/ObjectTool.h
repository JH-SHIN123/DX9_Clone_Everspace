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
	void Setting_ObjectData(); // 안씀

public:
	CListBox m_ListBoxObject;	// 오브젝트 프로토 타입 리스트박스
	CListBox m_ListAddedCom;	// 오브젝트 프로토 타입이 가지고 있는 컴포넌트들
	CListBox m_ListComponent;	// 추가 가능한 컴포넌트 목록
	CListBox m_ListObject_Save;	// 저장 할 데이터 리스트

	_bool m_bListCheck = false;
	CString m_wstrPickedObject = _T("");	// 프로토타입 선택
	CString m_wstrPickedComponentTag = _T("");	// 컴포넌트 선택
	
	CString m_wstrObjectPrototype_Tag = _T("");	// L"Prototype" + m_wstrPickedObject
	CString m_wstrComponentProtoType_Tag = _T(""); // L"Prototype" + m_wstrPickedComponentTag

	CString m_wstrPickedObjectList_Tag_Save = _T(""); // 저장이 될 리스트의 ObjectTag

	map<CString, PASSDATA_OBJECT*> m_mapObjectData;
	D3DMATERIAL9 m_tMaterial;

	// key : tool에서 구별
	// value : 저장 데이터 PrototypeTag > Material > <vector>ComponentTags

	//CString m_wstrFileExtension = L".txt";					// 파일 확장자
	//CString m_wstrFilePath = L"../../Data/PrototypeData/";	// 저장될 경로
	


public:
	afx_msg void OnLbnSelchangeList1();	// Object Prototype List Picked
	afx_msg void OnLbnSelchangeList2();	// Added Components List (Save Data)
	afx_msg void OnLbnSelchangeList3();	// Component List
	afx_msg void OnLbnSelchangeList4();	// Save Object List (Save Data)
public:
	afx_msg void OnBnClickedButton1();	// Data 수정용
	afx_msg void OnBnClickedButton2();	// Add Component
	afx_msg void OnBnClickedButton5();	// Save
	afx_msg void OnBnClickedButton6();	// Load
	afx_msg void OnBnClickedButton8();	// Add Object List
	
	CString r2;
};

#endif // !__OBJECT_PROTOTYPE_TOOL_H__
