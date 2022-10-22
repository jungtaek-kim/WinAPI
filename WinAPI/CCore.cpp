#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CEventManager.h"
#include "CCollisionManager.h"
#include "CPathManager.h"

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
	EVENT->Init();
	COLLISION->Init();
	PATH->Init();

	SCENE->Init();
}

void CCore::Update()
{
	// ���� �����ӿ��� �߰��� �̺�Ʈ�� ������ �ʱ⿡ �Ѳ����� ó��
	EVENT->Update();

	TIME->Update();
	INPUT->Update();
	SCENE->Update();

	// ���� ������Ʈ���� ������Ʈ �� �� �浹ó�� ����
	COLLISION->Update();
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
	SCENE->Release();

	TIME->Release();
	RENDER->Release();
	INPUT->Release();
	EVENT->Release();
	COLLISION->Release();
	PATH->Release();
}
