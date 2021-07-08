#pragma once
#ifndef __VIBUFFER_HEXAGONCOLOR_H__

USING(Engine)
#include "VIBuffer.h"
class  CVIBuffer_HexagonTex final : public CVIBuffer
{
private:
	explicit CVIBuffer_HexagonTex(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer_HexagonTex(const CVIBuffer_HexagonTex& other);
	virtual ~CVIBuffer_HexagonTex() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;
	virtual _uint Render_VIBuffer() override;

public:
	static CVIBuffer_HexagonTex* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

public:
	void SetVB(_float3 VB1, _float3 VB2, _float3 VB3
		, _float3 VB4, _float3 VB5, _float3 VB6);
};


#define __VIBUFFER_HEXAGONCOLOR_H__
#endif