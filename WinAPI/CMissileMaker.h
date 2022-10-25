#pragma once
#include "CGameObject.h"
class CMissileMaker : public CGameObject
{
public:
	CMissileMaker();
	virtual ~CMissileMaker();

private:
	float m_fLastShootTime;
	float m_fRepeatTime;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

public:
	float GetRepeatTime();
	void SetRepeatTime(float repeatTime);

	void LevelUp();

private:
	void CreateRandomMissile();
};

