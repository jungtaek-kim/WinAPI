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
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		(*iter)->Init();
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
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		if ((*iter)->GetReserveDelete())	// 게임오브젝트가 삭제 예정인경우
			(*iter)->SetSafeToDelete();		// 삭제해도 괜찮은 상태로 전환
		else
			(*iter)->Update();
	}

	// 상속한 자식 로직갱신
	Update();

	// 씬 내에 삭제해도 안전한 게임오브젝트를 삭제
	iter = m_listObj.begin();
	while (iter != m_listObj.end())
	{
		if ((*iter)->GetSafeToDelete())
		{
			delete (*iter);
			iter = m_listObj.erase(iter);
		}
		else
			iter++;
	}
}

void CScene::SceneRender()
{
	// 씬 내에 모든 게임오브젝트 표현갱신
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		(*iter)->Render();
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
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		(*iter)->Release();
		delete (*iter);
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
