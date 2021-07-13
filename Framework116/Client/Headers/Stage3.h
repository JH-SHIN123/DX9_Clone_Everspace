#pragma once

#ifndef __STAGE3_H__
#include "Scene.h"

USING(Engine)

class CStage3 final : public CScene
{
public:
	explicit CStage3(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CStage3() = default;

public:
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(_float fDeltaTime) override;
	virtual _uint LateUpdate_Scene(_float fDeltaTime) override;

public:
	static CStage3* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

};

#define __STAGE3_H__
#endif
