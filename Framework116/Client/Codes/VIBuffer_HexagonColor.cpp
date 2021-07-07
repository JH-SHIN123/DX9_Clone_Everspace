#include"stdafx.h"
#include "..\Headers\VIBuffer_HexagonColor.h"

CVIBuffer_HexagonColor::CVIBuffer_HexagonColor(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
{
}

CVIBuffer_HexagonColor::CVIBuffer_HexagonColor(const CVIBuffer_HexagonColor & other)
	: CVIBuffer(other)
{
}

HRESULT CVIBuffer_HexagonColor::Ready_Component_Prototype()
{
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iIndexSize = sizeof(INDEX16);
	m_IndexFmt = D3DFMT_INDEX16;
	m_iFVF = FVF_VTX_COLOR;
	m_iVertexCount = 6;
	m_iTriCount = 4;

	CVIBuffer::Ready_Component_Prototype();

	VTX_COLOR* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = _float3(0.f, 1.f, 0.f);
	pVertices[0].iColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	pVertices[1].vPosition = _float3(1.f, 0.5f, 0.f);
	pVertices[1].iColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	pVertices[2].vPosition = _float3(1.f, -0.5f, 0.f);
	pVertices[2].iColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	pVertices[3].vPosition = _float3(0.f, -1.f, 0.f);
	pVertices[3].iColor = D3DCOLOR_ARGB(255, 0, 0,255);	

	pVertices[4].vPosition = _float3(-1.f, -0.5f, 0.f);
	pVertices[4].iColor = D3DCOLOR_ARGB(255, 0, 0, 255);
	
	pVertices[5].vPosition = _float3(-1.f, 0.5f, 0.f);
	pVertices[5].iColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pVB->Unlock();

	INDEX16* pIndices = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 5;
	pIndices[0]._2 = 0;
	pIndices[0]._3 = 1;

	pIndices[1]._1 = 4;
	pIndices[1]._2 = 5;
	pIndices[1]._3 = 1;

	pIndices[2]._1 = 4;
	pIndices[2]._2 = 1;
	pIndices[2]._3 = 2;

	pIndices[3]._1 = 4;
	pIndices[3]._2 = 2;
	pIndices[3]._3 = 3;


	m_pIB->Unlock();


	return S_OK;
}

HRESULT CVIBuffer_HexagonColor::Ready_Component(void * pArg)
{
	CVIBuffer::Ready_Component(pArg);

	return S_OK;
}

_uint CVIBuffer_HexagonColor::Render_VIBuffer()
{
	if (CVIBuffer::Render_VIBuffer())
		return RENDER_ERROR;	

	if (FAILED(m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount)))
	{
		PRINT_LOG(L"Error", L"Failed To DrawIndexedPrimitive");
		return RENDER_ERROR;
	}

	return NO_EVENT;
}

CVIBuffer_HexagonColor * CVIBuffer_HexagonColor::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CVIBuffer_HexagonColor* pInstance = new CVIBuffer_HexagonColor(pDevice);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create VIBuffer TriColor");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_HexagonColor::Clone(void * pArg)
{
	CVIBuffer_HexagonColor* pClone = new CVIBuffer_HexagonColor(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone VIBuffer TriColor");
		Safe_Release(pClone);
	}

	return pClone;
}

void CVIBuffer_HexagonColor::Free()
{
	CVIBuffer::Free();
}
