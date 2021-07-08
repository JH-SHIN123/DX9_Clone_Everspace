#include"stdafx.h"
#include "..\Headers\VIBuffer_HexagonTex.h"

CVIBuffer_HexagonTex::CVIBuffer_HexagonTex(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
{
}

CVIBuffer_HexagonTex::CVIBuffer_HexagonTex(const CVIBuffer_HexagonTex & other)
	: CVIBuffer(other)
{
}

HRESULT CVIBuffer_HexagonTex::Ready_Component_Prototype()
{
	m_iVertexSize = sizeof(VTX_TEXTURE);
	m_iIndexSize = sizeof(INDEX16);
	m_IndexFmt = D3DFMT_INDEX16;
	m_iFVF = FVF_VTX_TEXTURE;
	m_iVertexCount = 7;
	m_iTriCount = 6;

	CVIBuffer::Ready_Component_Prototype();

	VTX_TEXTURE* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = _float3(0.f, 0.f, 0.f);
	pVertices[0].vUV = _float2(0.5f, 0.5f);

	pVertices[1].vPosition = _float3(0.f, 1.f, 0.f);
	pVertices[1].vUV = _float2(0.5f, 0.f);

	pVertices[2].vPosition = _float3(1.f, 0.5f, 0.f);
	pVertices[2].vUV = _float2(1.f, 0.25f);

	pVertices[3].vPosition = _float3(1.f, -0.5f, 0.f);
	pVertices[3].vUV = _float2(1.f, 0.75f);

	pVertices[4].vPosition = _float3(0.f, -1.f, 0.f);
	pVertices[4].vUV = _float2(0.5f, 1.f);

	pVertices[5].vPosition = _float3(-1.f, -0.5f, 0.f);
	pVertices[5].vUV = _float2(0.f, 0.75f);
	
	pVertices[6].vPosition = _float3(-1.f, 0.5f, 0.f);
	pVertices[6].vUV = _float2(0.f, 0.25f);


	m_pVB->Unlock();

	INDEX16* pIndices = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 0;
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;

	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;

	pIndices[2]._1 = 0;
	pIndices[2]._2 = 3;
	pIndices[2]._3 = 4;

	pIndices[3]._1 = 0;
	pIndices[3]._2 = 4;
	pIndices[3]._3 = 5;

	pIndices[4]._1 = 0;
	pIndices[4]._2 = 5;
	pIndices[4]._3 = 6;

	pIndices[5]._1 = 0;
	pIndices[5]._2 = 6;
	pIndices[5]._3 = 1;

	m_pIB->Unlock();


	return S_OK;
}

HRESULT CVIBuffer_HexagonTex::Ready_Component(void * pArg)
{
	CVIBuffer::Ready_Component(pArg);

	return S_OK;
}

_uint CVIBuffer_HexagonTex::Render_VIBuffer()
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

CVIBuffer_HexagonTex * CVIBuffer_HexagonTex::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CVIBuffer_HexagonTex* pInstance = new CVIBuffer_HexagonTex(pDevice);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create VIBuffer TriColor");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_HexagonTex::Clone(void * pArg)
{
	CVIBuffer_HexagonTex* pClone = new CVIBuffer_HexagonTex(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone VIBuffer TriColor");
		Safe_Release(pClone);
	}

	return pClone;
}

void CVIBuffer_HexagonTex::Free()
{
	CVIBuffer::Free();
}

void CVIBuffer_HexagonTex::SetVB(_float3 VB1, _float3 VB2, _float3 VB3, _float3 VB4, _float3 VB5, _float3 VB6)
{
	VTX_TEXTURE* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = _float3(0.f, 0.f, 0.f);
	pVertices[0].vUV = _float2(0.5f, 0.5f);

	pVertices[1].vPosition = VB1;
	pVertices[1].vUV = _float2(0.5f, 0.f);

	pVertices[2].vPosition = VB2;
	pVertices[2].vUV = _float2(1.f, 0.25f);

	pVertices[3].vPosition = VB3;
	pVertices[3].vUV = _float2(1.f, 0.75f);


	pVertices[4].vPosition = VB4;
	pVertices[4].vUV = _float2(0.5f, 1.f);

	pVertices[5].vPosition = VB5;
	pVertices[5].vUV = _float2(0.f, 0.75f);

	pVertices[6].vPosition = VB6;
	pVertices[6].vUV = _float2(0.f, 0.25f);


	m_pVB->Unlock();
}


