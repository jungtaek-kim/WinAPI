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
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f - 40, L"�ְ� ���� : " + to_wstring(GAME->GetHighScore()));
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f- 20, L"���� ���� : " + to_wstring(GAME->GetScore()));
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f + 10, L"�ٽ� �����Ϸ��� �����̽��� Ű�� ��������");
}

void CSceneScore::Exit()
{
}

void CSceneScore::Release()
{
}
