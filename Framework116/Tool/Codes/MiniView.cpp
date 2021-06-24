// ../Codes/CMiniView.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "../Headers/MiniView.h"
#include <MainFrm.h>
#include "MainView.h"
#include "Device_Manager.h"
#include "MainScene.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
	: m_pManagement(CManagement::Get_Instance())
	, m_bOnce(false)
{

}

CMiniView::~CMiniView()
{
	Safe_Release(m_pDevice);
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()

void CMiniView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	// m_hWnd = g_hWnd;
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

// CMiniView 그리기

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	if (!m_bOnce)
	{
		CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
		CMainView* pView = dynamic_cast<CMainView*>(pMain->m_tMainSplitterWnd.GetPane(0, 1));
		pView->Ready_StaticResources();
		pView->Setup_DefaultSetting();

		m_pDevice = m_pManagement->Get_Device();
		Safe_AddRef(m_pDevice);

		if (nullptr == m_pDevice)
		{
			PRINT_LOG(L"Error", L"m_pDevice is nullptr");
			return;
		}
		
	}
	m_pManagement->Update_Game();

	// TODO: 여기에 그리기 코드를 추가합니다.

	

}


// CMiniView 진단

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기
