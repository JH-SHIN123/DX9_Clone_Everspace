#pragma once
#ifndef __CAMERA_H__

#include "GameObject.h"

BEGIN(Engine)
typedef struct tagCameraDesc : public BASE_DESC
{
	_float4x4 matView;
	_float3 vEye = _float3(0.f, 0.f, 0.f);
	_float3 vAt = _float3(0.f, 0.f, 0.f);
	_float3 vUp = _float3(0.f, 1.f, 0.f);

	_float4x4 matProj;
	_float fFovY = 0.f;
	_float fAspect = 0.f;
	_float fNear = 0.f;
	_float fFar = 0.f;

	_float4x4 matOrtho;
	_uint iWinCx = 0;
	_uint iWinCy = 0;
}CAMERA_DESC;

class ENGINE_DLL CCamera abstract :	public CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CCamera(const CCamera& other);
	virtual ~CCamera() = default;

public:
	void Set_ProjectionType(const EProjectionType _eType) { m_eProjectionType = _eType; }

public:
	const CAMERA_DESC& Get_CameraDesc() const;

public:
	virtual HRESULT Ready_GameObject_Prototype() = 0;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) = 0;
	virtual _uint Update_GameObject(_float fDeltaTime) = 0;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) = 0;
	virtual _uint Render_GameObject() = 0;

public:
	virtual CGameObject * Clone(void * pArg = nullptr) = 0;
	virtual void Free() = 0;

protected:
	CAMERA_DESC	m_CameraDesc;
	EProjectionType m_eProjectionType = EProjectionType::Perspective;
};
END

#define __CAMERA_H__
#endif
