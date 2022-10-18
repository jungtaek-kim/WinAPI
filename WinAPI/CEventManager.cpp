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
	m_listAddObject.push_back(pObj);
}

void CEventManager::EventDeleteObject(CGameObject* pObj)
{
	// ���� ������ ���ӿ�����Ʈ�� �ڷᱸ���� ����
	m_listDeleteObject.push_back(pObj);
}

void CEventManager::EventChangeScene(GroupScene scene)
{
	// �� ��ȯ �̺�Ʈ�� �ڷᱸ���� ����
	m_listChangeScene.push_back(scene);
}

void CEventManager::ProgressAddObject()
{
	// �������� �ʱ⿡ �߰��� ���ӿ�����Ʈ�� �߰�

	for (CGameObject* pGameObject : m_listAddObject)
	{
		SCENE->GetCurScene()->AddGameObject(pGameObject);
	}
	m_listAddObject.clear();
}

void CEventManager::ProgressDeleteObject()
{
	// ���� ������ ���ӿ�����Ʈ�� �������� ǥ�ø� ����

	for (CGameObject* pGameObject : m_listDeleteObject)
	{
		pGameObject->SetReserveDelete();
	}
	m_listDeleteObject.clear();
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
