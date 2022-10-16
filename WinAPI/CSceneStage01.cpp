#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CSceneManager.h"

#include "CPlayer.h"

CSceneStage01::CSceneStage01()
{
	player = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	player = new CPlayer();
	player->SetPos(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
}

void CSceneStage01::Enter()
{
}

void CSceneStage01::Update()
{
	player->Update();

	if (BUTTONDOWN(VK_ESCAPE))
	{
		SCENE->ChangeScene(GroupScene::Title);
	}
}

void CSceneStage01::Render()
{
	player->Render();
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
	player->Release();
	delete player;
}
