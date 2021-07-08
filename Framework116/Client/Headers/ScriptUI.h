#pragma once
#ifndef __SCRIPTUI_H__

#include "GameObject.h"
#include "UI.h"

USING(Engine)

enum class EScript {
	Tutorial, End
};

class CScriptUI final : public CUI
{
public:
	explicit CScriptUI(LPDIRECT3DDEVICE9 pDevice);
	explicit CScriptUI(const CScriptUI& other);
	virtual ~CScriptUI() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

public:
	_uint Set_NextScript();
	_uint Set_Script(EScript eScript);

private:
	void Check_BlackBar(_float fDeltaTime); // 대화의 시작
	HRESULT Add_Layer_UI(const wstring& LayerTag, const UI_DESC* pUIDesc);
	_uint Script_Check();
	void Script_Tutorial();


public:
	static CScriptUI* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	EScript m_eScriptMode = EScript::End;
	wstring m_wstrName = L"";
	wstring m_wstrScript = L"";
	RECT m_tPortrait;
	DWORD m_dwScriptNext;	// 다음 대화
	DWORD m_dwScriptCount;	// 한글자씩 끊어서 출력
	DWORD m_dwScriptCountMax;// 최대치
	_float m_fScriptTime;	// 끊어서 출력 시간
	_bool m_IsPlayerPortrait = false;
	_bool m_IsStartScript = true;
	_bool m_IsEndScript = false;
	_float m_fShowBlackBar = 3.f;

private:	// m_pTransform = 대화 창
	CTransform* m_pTransfrom_Portrait = nullptr;
	CTransform* m_pTransfrom_Name = nullptr;
	CTransform* m_pTransfrom_BlackBar_Up = nullptr;
	CTransform* m_pTransfrom_BlackBar_Down = nullptr;


};

#define __SCRIPTUI_H__
#endif