#include "framework.h"
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CGameObject.h"

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
	ProgressDeleteObject();

	// 씬 전환은 다른 이벤트보다 가장 마지막에 진행
	ProgressChangeScene();
}

void CEventManager::Release()
{
}

void CEventManager::EventAddObject(CGameObject* pObj)
{
	// 다음 프레임에 추가될 게임오브젝트를 자료구조에 보관
	m_listAddObject.push_back(pObj);
}

void CEventManager::EventDeleteObject(CGameObject* pObj)
{
	// 삭제 예정인 게임오브젝트를 자료구조에 보관
	m_listDeleteObject.push_back(pObj);
}

void CEventManager::EventChangeScene(GroupScene scene)
{
	// 씬 전환 이벤트를 자료구조에 보관
	m_listChangeScene.push_back(scene);
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

void CEventManager::ProgressDeleteObject()
{
	// 삭제 예정인 게임오브젝트에 삭제예정 표시를 진행

	list<CGameObject*>::iterator iter;
	for (iter = m_listDeleteObject.begin();
		iter != m_listDeleteObject.end();
		iter++)
	{
		(*iter)->SetReserveDelete();
	}
	m_listDeleteObject.clear();
}

void CEventManager::ProgressChangeScene()
{
	// 저장된 씬 전환 이벤트 중 가장 마지막의 이벤트만 진행

	if (m_listChangeScene.empty())
		return;

	GroupScene scene = m_listChangeScene.back();
	m_listChangeScene.clear();
	SCENE->ChangeScene(scene);
}
