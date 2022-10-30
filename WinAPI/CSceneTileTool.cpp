#include "framework.h"
#include "CSceneTileTool.h"

#include "CInputManager.h"
#include "CEventManager.h"

#include "CTile.h"

CSceneTileTool::CSceneTileTool()
{
}

CSceneTileTool::~CSceneTileTool()
{
}

void CSceneTileTool::Init()
{
	CTile* pTile1 = new CTile;
	pTile1->SetTileIndex(1);
	pTile1->SetTilePos(1, 1);
	AddGameObject(pTile1);
}

void CSceneTileTool::Enter()
{
}

void CSceneTileTool::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GroupScene::Title);
	}
}

void CSceneTileTool::Render()
{
}

void CSceneTileTool::Exit()
{
}

void CSceneTileTool::Release()
{
}
