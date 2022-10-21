#pragma once
#include "CGameObject.h"
class CMonster : public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

