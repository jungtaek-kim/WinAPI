#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
}

void CSceneTitle::Enter()
{
}

void CSceneTitle::Update()
{
	if (BUTTONDOWN(VK_SPACE))
	{
		SCENE->ChangeScene(GroupScene::Stage01);
	}
}

void CSceneTitle::Render()
{
	RENDER->SetText(TextType::Center);
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f, L"press space to start");
}

void CSceneTitle::Exit()
{
}

void CSceneTitle::Release()
{
}