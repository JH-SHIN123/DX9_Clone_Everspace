#include "pch.h"
#include "Dummy.h"
#include "GeometryMesh.h"

CDummy::CDummy(LPDIRECT3DDEVICE9 pDevice)
    : CGameObject(pDevice)
{
}

CDummy::CDummy(const CDummy& other)
    : CGameObject(other)
{
}

HRESULT CDummy::Ready_GameObject_Prototype()
{
    CGameObject::Ready_GameObject_Prototype();

    return S_OK;
}

HRESULT CDummy::Ready_GameObject(void* pArg)
{
    CGameObject::Ready_GameObject(pArg);

    DUMMY_DESC* pDummyDesc = nullptr;
    wstring wstrMeshPrototypeTag = L"";
    TRANSFORM_DESC tTransformDesc;
    if (auto ptr = (BASE_DESC*)pArg)
    {
        if (pDummyDesc = dynamic_cast<DUMMY_DESC*>(ptr))
        {
            wstrMeshPrototypeTag = pDummyDesc->wstrMeshPrototypeTag;
            tTransformDesc = pDummyDesc->tTransformDesc;
        }
    }

    // For.Com_Mesh
    if (FAILED(CGameObject::Add_Component(
        EResourceType::Static,
        wstrMeshPrototypeTag,
        L"Com_Mesh",
        (CComponent**)&m_pMesh)))
    {
        PRINT_LOG(L"Error", L"Failed To Add_Component Component_Mesh_Axis");
        return E_FAIL;
    }

    // For.Com_Transform
    TRANSFORM_DESC TransformDesc = tTransformDesc;
    TransformDesc.fSpeedPerSec = 0.f;
    TransformDesc.fRotatePerSec = 0.f;

    if (FAILED(CGameObject::Add_Component(
        EResourceType::Static,
        L"Component_Transform",
        L"Com_Transform",
        (CComponent**)&m_pTransform,
        &TransformDesc)))
    {
        PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
        return E_FAIL;
    }

    return S_OK;
}

_uint CDummy::Update_GameObject(_float fDeltaTime)
{
    CGameObject::Update_GameObject(fDeltaTime);

    return _uint();
}

_uint CDummy::LateUpdate_GameObject(_float fDeltaTime)
{
    CGameObject::LateUpdate_GameObject(fDeltaTime);

    if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::NonAlpha, this)))
        return UPDATE_ERROR;

    return _uint();
}

_uint CDummy::Render_GameObject()
{
    CGameObject::Render_GameObject();

    m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);

    if (m_pMesh)
        m_pMesh->Render_Mesh();

    return _uint();
}

CDummy* CDummy::Create(LPDIRECT3DDEVICE9 pDevice)
{
    CDummy* pInstance = new CDummy(pDevice);
    if (FAILED(pInstance->Ready_GameObject_Prototype()))
    {
        PRINT_LOG(L"Error", L"Failed To Create CDummy");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CDummy::Clone(void* pArg)
{
    CDummy* pClone = new CDummy(*this); /* 복사 생성자 호출 */
    if (FAILED(pClone->Ready_GameObject(pArg)))
    {
        PRINT_LOG(L"Error", L"Failed To Clone CDummy");
        Safe_Release(pClone);
    }

    return pClone;
}

void CDummy::Free()
{
    Safe_Release(m_pMesh);
    Safe_Release(m_pTransform);

    CGameObject::Free();
}
