#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(200, WINSIZEY * 0.5f);
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1000, WINSIZEY * 0.5f);
	AddGameObject(pMonster);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);
}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(1.f);
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(1.f);
		CHANGESCENE(GroupScene::Title);
	}
}

void CSceneStage01::Render()
{
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
