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
	// ���� �����ӿ� �߰��� ���ӿ�����Ʈ�� �ڷᱸ���� ����
	m_listAddObject.push_back(pObj);
}

void CEventManager::ProgressAddObject()
{
	// �������� �ʱ⿡ �߰��� ���ӿ�����Ʈ�� �߰�

	list<CGameObject*>::iterator iter;
	for (iter = m_listAddObject.begin();
		iter != m_listAddObject.end();
		iter++)
	{
		SCENE->GetCurScene()->AddGameObject(*iter);
	}
	m_listAddObject.clear();
}
