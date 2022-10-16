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
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	CPlayer* pPlayer1 = new CPlayer();
	pPlayer1->SetPos(WINSIZEX * 0.5f - 200, WINSIZEY * 0.5f);
	AddGameObject(pPlayer1);

	CPlayer* pPlayer2 = new CPlayer();
	pPlayer2->SetPos(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	AddGameObject(pPlayer2);

	CPlayer* pPlayer3 = new CPlayer();
	pPlayer3->SetPos(WINSIZEX * 0.5f + 200, WINSIZEY * 0.5f);
	AddGameObject(pPlayer3);

}

void CSceneStage01::Enter()
{
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		SCENE->ChangeScene(GroupScene::Title);
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
