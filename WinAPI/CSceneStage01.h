#pragma once
#include "CScene.h"

class CPlayer;

class CSceneStage01 : public CScene
{
private:
	CPlayer* player;

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
