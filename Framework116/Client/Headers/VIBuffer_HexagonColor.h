#pragma once
#ifndef __VIBUFFER_HEXAGONCOLOR_H__

USING(Engine)
#include "VIBuffer.h"
class  CVIBuffer_HexagonColor final : public CVIBuffer
{
private:
	explicit CVIBuffer_HexagonColor(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer_HexagonColor(const CVIBuffer_HexagonColor& other);
	virtual ~CVIBuffer_HexagonColor() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;
	virtual _uint Render_VIBuffer() override;

public:
	static CVIBuffer_HexagonColor* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;
};


#define __VIBUFFER_HEXAGONCOLOR_H__
#endif