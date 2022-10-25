#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CGameManager.h"

#include "CPlayer.h"
#include "CMissile.h"
#include "CMonster.h"
#include "CMissileMaker.h"

CSceneStage01::CSceneStage01()
{
	m_fScore = 0;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
}

void CSceneStage01::Enter()
{
	srand((unsigned int)time(nullptr));

	CPlayer* pPlayer = new CPlayer();
	pPlayer->SetPos(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	AddGameObject(pPlayer);

	pMissileMaker = new CMissileMaker;
	pMissileMaker->SetRepeatTime(0.1f);
	AddGameObject(pMissileMaker);

	m_fScore = 0;
	GAME->SetScore(0);
}

void CSceneStage01::Update()
{
	m_fScore += DT;
	GAME->SetScore(m_fScore);

	m_fLevelUpCount += DT;
	if (m_fLevelUpCount > 3.f)
	{
		m_fLevelUpCount = 0;
		pMissileMaker->LevelUp();
	}
		

	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GroupScene::Title);
	}
}

void CSceneStage01::Render()
{
	RENDER->Text(WINSIZEX * 0.5f, 10, L"최고 점수 : " + to_wstring(GAME->GetHighScore()));
	RENDER->Text(WINSIZEX * 0.5f, 30, L"현재 점수 : " + to_wstring(GAME->GetScore()));
}

void CSceneStage01::Exit()
{
	DeleteAllObject();
	GAME->SetScore(m_fScore);
}

void CSceneStage01::Release()
{
}
