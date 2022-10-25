#pragma once
#include "CGameObject.h"

class CPlayer : public CGameObject
{
private:
	float m_fSpeed = 300.0f;

public:
	CPlayer();
	virtual ~CPlayer();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};