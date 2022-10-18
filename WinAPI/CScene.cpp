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
		pGameObject->Init();
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
			pGameObject->Update();
	}

	// ����� �ڽ� ��������
	Update();

	// �� ���� �����ص� ������ ���ӿ�����Ʈ�� ����
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
	// �� ���� ��� ���ӿ�����Ʈ ǥ������
	for (CGameObject* pGameObject : m_listObj)
	{
		pGameObject->Render();
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
		pGameObject->Release();
		delete pGameObject;
	}

	// ����� �ڽ� ������
	Release();
}

void CScene::AddGameObject(CGameObject* pGameObj)
{
	// ���ο� ���ӿ�����Ʈ �߰� �� �ʱ�ȭ
	m_listObj.push_back(pGameObj);
	pGameObj->Init();
}
