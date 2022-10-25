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

	// �� ��ȯ�� �ٸ� �̺�Ʈ���� ���� �������� ����
	ProgressChangeScene();
}

void CEventManager::Release()
{
}

void CEventManager::EventAddObject(CGameObject* pObj)
{
	// ���� �����ӿ� �߰��� ���ӿ�����Ʈ�� �ڷᱸ���� ����
	m_queueAddObject.push(pObj);
}

void CEventManager::EventDeleteObject(CGameObject* pObj)
{
	// ���� ������ ���ӿ�����Ʈ�� �ڷᱸ���� ����
	m_queueDeleteObject.push(pObj);
}

void CEventManager::EventChangeScene(GroupScene scene)
{
	// �� ��ȯ �̺�Ʈ�� �ڷᱸ���� ����
	m_listChangeScene.push_back(scene);
}

void CEventManager::ProgressAddObject()
{
	// �������� �ʱ⿡ �߰��� ���ӿ�����Ʈ�� �߰�

	while (!m_queueAddObject.empty())
	{
		CGameObject* pGameObject = m_queueAddObject.front();
		m_queueAddObject.pop();
		SCENE->GetCurScene()->AddGameObject(pGameObject);
	}
}

void CEventManager::ProgressDeleteObject()
{
	// ���� ������ ���ӿ�����Ʈ�� �������� ǥ�ø� ����

	while (!m_queueDeleteObject.empty())
	{
		CGameObject* pGameObject = m_queueDeleteObject.front();
		m_queueDeleteObject.pop();
		pGameObject->SetReserveDelete();
	}
}

void CEventManager::ProgressChangeScene()
{
	// ����� �� ��ȯ �̺�Ʈ �� ���� �������� �̺�Ʈ�� ����

	if (m_listChangeScene.empty())
		return;

	GroupScene scene = m_listChangeScene.back();
	m_listChangeScene.clear();
	SCENE->ChangeScene(scene);
}
