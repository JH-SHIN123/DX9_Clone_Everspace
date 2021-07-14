#include "stdafx.h"
#include "Delivery.h"

CDelivery::CDelivery(LPDIRECT3DDEVICE9 pDevice) :
    CGameObject(pDevice)
{
}

CDelivery::CDelivery(const CDelivery& other)
    : CGameObject(other)
{
}

HRESULT CDelivery::Ready_GameObject_Prototype()
{
    CGameObject::Ready_GameObject_Prototype();

    return S_OK;
}

HRESULT CDelivery::Ready_GameObject(void* pArg)
{
    CGameObject::Ready_GameObject(pArg);

    GAMEOBJECT_DESC* pDesc = nullptr;
    if (auto ptr = (BASE_DESC*)pArg)
    {
        if (pDesc = dynamic_cast<GAMEOBJECT_DESC*>(ptr))
        {
        }
        else
        {
            PRINT_LOG(L"Error", L"CBrokenPlane is nullptr");
            return E_FAIL;
        }
    }

    // For.Com_Mesh
    if (FAILED(CGameObject::Add_Component(
        EResourceType::Static,
        L"Component_Mesh_Delivery",
        L"Com_Mesh",
        (CComponent**)&m_pMesh)))
    {
        PRINT_LOG(L"Error", L"Failed To Add_Component Com_Mesh");
        return E_FAIL;
    }

    // For.Com_Transform
    TRANSFORM_DESC TransformDesc = pDesc->tTransformDesc;

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

    // For.Com_Collide
    PASSDATA_COLLIDE tCollide;
    CStreamHandler::Load_PassData_Collide(L"delivery", L"Component_Mesh_Delivery", tCollide);
    m_Collides.reserve(tCollide.vecBoundingSphere.size());
    int i = 0;
    for (auto& bounds : tCollide.vecBoundingSphere) {
        if (FAILED(CGameObject::Add_Component(
            EResourceType::Static,
            L"Component_CollideSphere",
            L"Com_CollideSphere" + to_wstring(i++),
            nullptr,
            &bounds,
            true)))
        {
            PRINT_LOG(L"Error", L"Failed To Add_Component Com_Transform");
            return E_FAIL;
        }
    }

    return S_OK;
}

_uint CDelivery::Update_GameObject(_float fDeltaTime)
{
    if (m_IsDead) return DEAD_OBJECT;
    CGameObject::Update_GameObject(fDeltaTime);
    Movement(fDeltaTime);

    m_pTransform->Update_Transform_Quaternion();
    for (auto& p : m_Collides)
    {
        if (p) p->Update_Collide(m_pTransform->Get_TransformDesc().matWorld);
    }
    return NO_EVENT;
}

_uint CDelivery::LateUpdate_GameObject(_float fDeltaTime)
{
    if (m_IsDead) return DEAD_OBJECT;

    CGameObject::LateUpdate_GameObject(fDeltaTime);

    if (FAILED(m_pManagement->Add_GameObject_InRenderer(ERenderType::NonAlpha, this)))
        return UPDATE_ERROR;

    return _uint();
}

_uint CDelivery::Render_GameObject()
{
    CGameObject::Render_GameObject();

    m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransform->Get_TransformDesc().matWorld);
    m_pMesh->Render_Mesh();

#ifdef _DEBUG // Render Collide
    for (auto& p : m_Collides)
        if (p) p->Render_Collide();
#endif

    return _uint();
}

_uint CDelivery::Movement(_float fDeltaTime)
{
    return _uint();
}

CDelivery* CDelivery::Create(LPDIRECT3DDEVICE9 pDevice)
{
    CDelivery* pInstance = new CDelivery(pDevice);
    if (FAILED(pInstance->Ready_GameObject_Prototype()))
    {
        PRINT_LOG(L"Error", L"Failed To Create Player");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CDelivery::Clone(void* pArg)
{
    CDelivery* pClone = new CDelivery(*this); /* 복사 생성자 호출 */
    if (FAILED(pClone->Ready_GameObject(pArg)))
    {
        PRINT_LOG(L"Error", L"Failed To Clone Player");
        Safe_Release(pClone);
    }

    return pClone;
}

void CDelivery::Free()
{
    Safe_Release(m_pTransform);
    Safe_Release(m_pMesh);

    CGameObject::Free();
}
