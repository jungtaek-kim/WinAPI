#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"

#include "CSceneTitle.h"
#include "CSceneStage01.h"

CCore::CCore()
{
	pCurScene		= nullptr;
	pSceneTitle		= nullptr;
	pSceneStage01	= nullptr;
}

CCore::~CCore()
{

}

void CCore::Init()
{
	TIME->Init();
	RENDER->Init();
	INPUT->Init();

	pSceneTitle = new CSceneTitle;
	pSceneTitle->Init();
	pSceneStage01 = new CSceneStage01;
	pSceneStage01->Init();

	pCurScene = pSceneTitle;
	pCurScene->Enter();
}

void CCore::Update()
{
	TIME->Update();
	INPUT->Update();
	pCurScene->Update();

	if (BUTTONDOWN(VK_SPACE))
	{
		pCurScene->Exit();
		pCurScene = pSceneStage01;
		pCurScene->Enter();
	}
	else if (BUTTONDOWN(VK_ESCAPE))
	{
		pCurScene->Exit();
		pCurScene = pSceneTitle;
		pCurScene->Enter();
	}
}

void CCore::Render()
{
	RENDER->BeginDraw();

	//// ���� ǥ�� ����
	pCurScene->Render();

	//// ���ܿ� ���� ����FPS ��� (60������ �̻��� ��ǥ�� ����ȭ �ؾ���)
	wstring frame = to_wstring(FPS);
	RENDER->Text(WINSIZEX - 50, 10, frame);

	RENDER->EndDraw();
}

void CCore::Release()
{
	TIME->Release();
	RENDER->Release();
	INPUT->Release();

	pCurScene->Exit();

	pSceneTitle->Release();
	pSceneStage01->Release();
}