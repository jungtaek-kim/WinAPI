#pragma once
#include "CComponent.h"

class CCollisionManager;
class CGameObject;

class CCollider : public CComponent
{
	friend CCollisionManager;
	friend CGameObject;

public:
	CCollider();
	virtual ~CCollider();

private:
	Vector m_vecPos;		// 충돌체의 위치
	Vector m_vecOffsetPos;	// 충돌체의 변위차(수정값)
	Vector m_vecScale;		// 충돌체의 크기

private:
	void SetPos(Vector pos);
	void SetOffsetPos(Vector offset);
	void SetScale(Vector scale);

public:
	Vector GetPos();
	Vector GetOffsetPos();
	Vector GetScale();

private:
	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;	// 충돌체의 물리처리
	void Render() override;
	void Release() override;

	// 충돌 시점 함수
private:
	void OnCollision(CCollider* pOtherCollider);	// 충돌중
};

