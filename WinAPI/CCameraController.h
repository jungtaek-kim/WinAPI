#pragma once
#include "CGameObject.h"
class CCameraController : public CGameObject
{
public:
	CCameraController();
	virtual ~CCameraController();

private:
	float m_fMouseTime = 1;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

