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
#include "CButton.h"
#include "CPanel.h"

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

	auto button1Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* pButton = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(pButton->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
	};

	CButton* pButton1 = new CButton;
	pButton1->SetName(L"버튼");
	pButton1->SetPos(100, 100);
	pButton1->SetScale(100, 100);
	pButton1->SetClickedCallback(button1Clicked, (DWORD_PTR)pButton1, (DWORD_PTR)1);
	AddGameObject(pButton1);

	CPanel* pPanel1 = new CPanel;
	pPanel1->SetName(L"패널1");
	pPanel1->SetPos(500, 100);
	pPanel1->SetScale(400, 400);
	pPanel1->SetDraggable(false);
	pPanel1->SetScreenFixed(false);
	AddGameObject(pPanel1);

	CButton* pButton2 = new CButton;
	pButton2->SetName(L"패널 안 버튼");
	pButton2->SetPos(100, 100);
	pButton2->SetScale(100, 100);
	pPanel1->AddChildUI(pButton2);

	CPanel* pPanel2 = new CPanel;
	pPanel2->SetName(L"패널2");
	pPanel2->SetPos(600, 200);
	pPanel2->SetScale(400, 400);
	AddGameObject(pPanel2);
}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.25f);
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
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
