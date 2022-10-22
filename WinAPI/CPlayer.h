#pragma once
#include "CGameObject.h"

class CImage;

class CPlayer : public CGameObject
{
private:
	float m_fSpeed = 200.0f;

public:
	CPlayer();
	virtual ~CPlayer();

private:
	CImage* m_pImg;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void CreateMissile();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};