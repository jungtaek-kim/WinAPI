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
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		(*iter)->Init();
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
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		if ((*iter)->GetReserveDelete())	// ���ӿ�����Ʈ�� ���� �����ΰ��
			(*iter)->SetSafeToDelete();		// �����ص� ������ ���·� ��ȯ
		else
			(*iter)->Update();
	}

	// ����� �ڽ� ��������
	Update();

	// �� ���� �����ص� ������ ���ӿ�����Ʈ�� ����
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
	// �� ���� ��� ���ӿ�����Ʈ ǥ������
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		(*iter)->Render();
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
	list<CGameObject*>::iterator iter;
	for (iter = m_listObj.begin();
		iter != m_listObj.end();
		iter++)
	{
		(*iter)->Release();
		delete (*iter);
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
