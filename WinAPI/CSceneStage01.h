#pragma once
#include "CScene.h"

class CSceneStage01 : public CScene
{
private:
	float m_pointX;
	float m_pointY;

public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
