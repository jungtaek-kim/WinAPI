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
	// �� ���� ��� ���ӿ�����Ʈ �ʱ�ȭ
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->GameObjectInit();
	}

	// ����� �ڽ� �ʱ�ȭ
	Init();
}

void CScene::SceneEnter()
{
	Enter();
}

void CScene::SceneUpdate()
{
	// �� ���� ��� ���ӿ�����Ʈ ��������
	for (CGameObject* pGameObject : m_listObj)
	{
		if (pGameObject->GetReserveDelete())
			pGameObject->SetSafeToDelete();
		else
			pGameObject->GameObjectUpdate();
	}

	// ����� �ڽ� ��������
	Update();

	// �� ���� �����ص� ������ ���ӿ�����Ʈ�� ����
	m_listObj.remove_if([](CGameObject* target)
		{
			if (target->GetSafeToDelete())
			{
				target->GameObjectRelease();
				delete target;
				return true;
			}
			else
				return false;
		});
}

void CScene::ScenePhysicsUpdate()
{
	// �� ���� ��� ���ӿ�����Ʈ ����ó�� ����
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->GameObjectPhysicsUpdate();
	}
}

void CScene::SceneRender()
{
	// �� ���� ��� ���ӿ�����Ʈ ǥ������
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->GameObjectRender();
	}

	// ����� �ڽ� ǥ������
	Render();
}

void CScene::SceneExit()
{
	Exit();
}

void CScene::SceneRelease()
{
	// �� ���� ��� ���ӿ�����Ʈ ������
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->GameObjectRelease();
		delete pGameObject;
	}
	m_listObj.clear();

	// ����� �ڽ� ������
	Release();
}

void CScene::AddGameObject(CGameObject* pGameObj)
{
	// ���ο� ���ӿ�����Ʈ �߰� �� �ʱ�ȭ
	m_listObj.push_back(pGameObj);
	pGameObj->GameObjectInit();
}
