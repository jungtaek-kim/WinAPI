#pragma once
#include "CGameObject.h"
class CMissile : public CGameObject
{
public:
	CMissile();
	virtual ~CMissile();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
};