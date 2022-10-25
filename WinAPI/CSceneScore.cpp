#include "framework.h"
#include "CSceneScore.h"

#include "CInputManager.h"
#include "CEventManager.h"
#include "CRenderManager.h"
#include "CGameManager.h"

CSceneScore::CSceneScore()
{
}

CSceneScore::~CSceneScore()
{
}

void CSceneScore::Init()
{
}

void CSceneScore::Enter()
{
	
}

void CSceneScore::Update()
{
	if (BUTTONDOWN(VK_SPACE))
	{
		CHANGESCENE(GroupScene::Title);
	}
}

void CSceneScore::Render()
{
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f - 40, L"최고 점수 : " + to_wstring(GAME->GetHighScore()));
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f- 20, L"현재 점수 : " + to_wstring(GAME->GetScore()));
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f + 10, L"다시 시작하려면 스페이스바 키를 누르세요");
}

void CSceneScore::Exit()
{
}

void CSceneScore::Release()
{
}
