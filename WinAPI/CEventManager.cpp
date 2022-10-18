#include "framework.h"
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CScene.h"

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Init()
{
}

void CEventManager::Update()
{
	ProgressAddObject();
}

void CEventManager::Release()
{
}

void CEventManager::EventAddObject(CGameObject* pObj)
{
	// 다음 프레임에 추가될 게임오브젝트를 자료구조에 보관
	m_listAddObject.push_back(pObj);
}

void CEventManager::ProgressAddObject()
{
	// 프레임의 초기에 추가될 게임오브젝트를 추가

	list<CGameObject*>::iterator iter;
	for (iter = m_listAddObject.begin();
		iter != m_listAddObject.end();
		iter++)
	{
		SCENE->GetCurScene()->AddGameObject(*iter);
	}
	m_listAddObject.clear();
}
