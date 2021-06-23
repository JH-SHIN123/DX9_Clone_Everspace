#include "pch.h"
#include "MainForm.h"


void CMainForm::OnBnObjectToolButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	if (nullptr == m_tObjectTool.GetSafeHwnd())
		m_tObjectTool.Create(IDD_OBJECTTOOL);
	m_tObjectTool.ShowWindow(SW_SHOW);
}
