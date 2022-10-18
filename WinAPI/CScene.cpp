#include "framework.h"
#include "CScene.h"

#include "CGameObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::SceneInit()
{
	// 씬 내에 모든 게임오브젝트 초기화
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->Init();
	}

	// 상속한 자식 초기화
	Init();
}

void CScene::SceneEnter()
{
	Enter();
}

void CScene::SceneUpdate()
{
	// 씬 내에 모든 게임오브젝트 로직갱신
	for (CGameObject* pGameObject : m_listObj)
	{
		if (pGameObject->GetReserveDelete())
			pGameObject->SetSafeToDelete();
		else
			pGameObject->Update();
	}

	// 상속한 자식 로직갱신
	Update();

	// 씬 내에 삭제해도 안전한 게임오브젝트를 삭제
	m_listObj.remove_if([](CGameObject* target)
		{
			if (target->GetSafeToDelete())
			{
				delete target;
				return true;
			}
			else
				return false;
		});
}

void CScene::SceneRender()
{
	// 씬 내에 모든 게임오브젝트 표현갱신
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->Render();
	}

	// 상속한 자식 표현갱신
	Render();
}

void CScene::SceneExit()
{
	Exit();
}

void CScene::SceneRelease()
{
	// 씬 내에 모든 게임오브젝트 마무리
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->Release();
		delete pGameObject;
	}

	// 상속한 자식 마무리
	Release();
}

void CScene::AddGameObject(CGameObject* pGameObj)
{
	// 새로운 게임오브젝트 추가 및 초기화
	m_listObj.push_back(pGameObj);
	pGameObj->Init();
}
