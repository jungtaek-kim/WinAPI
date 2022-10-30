#include "framework.h"
#include "CSceneTileTool.h"

#include "CInputManager.h"
#include "CEventManager.h"

CSceneTileTool::CSceneTileTool()
{
}

CSceneTileTool::~CSceneTileTool()
{
}

void CSceneTileTool::Init()
{
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
