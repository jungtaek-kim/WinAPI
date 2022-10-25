#pragma once
#include "CScene.h"

class CMissileMaker;

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CMissileMaker* pMissileMaker;
	float m_fScore;
	float m_fLevelUpCount;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
