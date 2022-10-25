#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"

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
		CHANGESCENE(GroupScene::Stage01);
	}
}

void CSceneTitle::Render()
{
	RENDER->SetText(TextType::Center);
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f - 10, L"���� 1.0");
	RENDER->Text(WINSIZEX * 0.5f, WINSIZEY * 0.5f + 10, L"�����Ϸ��� �����̽��� Ű�� ��������");
}

void CSceneTitle::Exit()
{
}

void CSceneTitle::Release()
{
}
