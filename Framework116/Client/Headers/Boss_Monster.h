#pragma once
#ifndef __BOSS_MONSTER_H__

#include "GameObject.h"

#define BOSSRANGE_NEAR		150.f
#define BOSSRANGE_MIDDLE	350.f
#define BOSSRANGE_FAR		450.f

USING(Engine)
class CBoss_Monster final : public CGameObject
{
public:
	explicit CBoss_Monster(LPDIRECT3DDEVICE9 pDevice);
	explicit CBoss_Monster(const CBoss_Monster& other);
	virtual ~CBoss_Monster() = default;

public:
	enum ActionMode {Near, Middle, Far, SpecialAction, End };

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual _uint Render_GameObject() override;

private: // Update 함수에 쓸 최상위 함수
	_uint Move_AI(_float fDeltaTime);
	_uint Attack_AI(_float fDeltaTime);

private: // Move_AI
	_uint Movement(_float fDeltaTime);
	_uint Move_Near(_float fDeltaTime);
	_uint Move_Middle(_float fDeltaTime);
	_uint Move_Far(_float fDeltaTime);
	
private: // Attack_AI
	//좌 우 포신과 플레이어의길이를 서로 비교 더 짧은 쪽이 발사!~ 
	_uint EnergyBallCannon_Target_Search(_float fDeltaTime);
	_uint Left_EnergyBall(_float fDeltaTime);
	_uint Right_EnergyBall(_float fDeltaTime);

private:
	_uint Fire_Triger(_float fDeltaTime); 
	_uint Fire_Laser(_float fDeltaTime);
	_uint Fire_EMP(_float fDeltaTime);
	_uint Spawn_Monster(_float fDeltaTime);
	_uint Spawn_Wormhole(_float fDeltaTime);

private: // Move_Mode
	void RotateMy_X(_float fDeltaTime);
	void RotateMy_Y(_float fDeltaTime);
	void RotateMy_Z(_float fDeltaTime);

private: // Add_HP_Bar
	_uint Add_Hp_Bar(_float fDeltaTime);

public:
	static CBoss_Monster* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

public:
	HRESULT Add_InLayer_MyParts();

private:
	CModelMesh*  m_pMesh = nullptr;
	CTransform* m_pTransform = nullptr;
	CTransform* m_pTargetTransform = nullptr;


private: /* AI */
	// 거리에 따라 행동을 다르게
	ActionMode m_eActionMode = End;
	_bool m_IsSpecialAction = false;

private:
	_float3 m_vRightCannonPosition;
	_float3 m_vLeftCannonPosition;
	_float m_fCannonLength = 40.f;
	_float m_fLeftCannonCoolTime = 0.f;
	_float m_fRightCannonCoolTime = 0.f;



private: /* Skills */
	// energyball
	_bool m_IsLeftFire = false;
	_float m_fEnergyBall_CoolTime = 0.f;

	// laser
	_float m_fLaser_CoolTime = 0.f;

	// emp bomb
	_float m_fEmpBomb_CoolTime = 0.f;

	// Spawn Monster
	_float m_fSpawnCoolTime = 0.f;

	// HP Bar 추가
	_bool m_IsHPBar = false;
	class CHP_Bar* m_pHp_Bar = nullptr;
	class CHP_Bar_Border* m_pHP_Bar_Border = nullptr;
	_float m_fHpLength = 64.f;
};

#define __BOSS_MONSTER_H__
#endif