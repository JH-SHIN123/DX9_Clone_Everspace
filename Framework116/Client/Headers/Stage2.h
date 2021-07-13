#pragma once

#ifndef __STAGE2_H__
#include "Scene.h"

USING(Engine)

class CStage2 final : public CScene
{
public:
	explicit CStage2(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CStage2() = default;

public:
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(_float fDeltaTime) override;
	virtual _uint LateUpdate_Scene(_float fDeltaTime) override;

public:
	static CStage2* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

};

#define __STAGE2_H__
#endif
