#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"

CCore::CCore()
{

}

CCore::~CCore()
{

}

void CCore::Init()
{
	TIME->Init();
	RENDER->Init();
	INPUT->Init();
	SCENE->Init();
}

void CCore::Update()
{
	TIME->Update();
	INPUT->Update();
	SCENE->Update();
}

void CCore::Render()
{
	RENDER->BeginDraw();

	//// ���� ǥ�� ����
	SCENE->Render();

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
	SCENE->Release();
}
