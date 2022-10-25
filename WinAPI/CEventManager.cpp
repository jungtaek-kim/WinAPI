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
	m_queueAddObject.push(pObj);
}

void CEventManager::EventDeleteObject(CGameObject* pObj)
{
	// 삭제 예정인 게임오브젝트를 자료구조에 보관
	m_queueDeleteObject.push(pObj);
}

void CEventManager::EventChangeScene(GroupScene scene)
{
	// 씬 전환 이벤트를 자료구조에 보관
	m_listChangeScene.push_back(scene);
}

void CEventManager::ProgressAddObject()
{
	// 프레임의 초기에 추가될 게임오브젝트를 추가

	while (!m_queueAddObject.empty())
	{
		CGameObject* pGameObject = m_queueAddObject.front();
		m_queueAddObject.pop();
		SCENE->GetCurScene()->AddGameObject(pGameObject);
	}
}

void CEventManager::ProgressDeleteObject()
{
	// 삭제 예정인 게임오브젝트에 삭제예정 표시를 진행

	while (!m_queueDeleteObject.empty())
	{
		CGameObject* pGameObject = m_queueDeleteObject.front();
		m_queueDeleteObject.pop();
		pGameObject->SetReserveDelete();
	}
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
