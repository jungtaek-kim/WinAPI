#include "framework.h"
#include "CScene.h"

#include "CCameraManager.h"
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
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectInit();
		}
	}

	// ����� �ڽ� �ʱ�ȭ
	Init();
}

void CScene::SceneEnter()
{
	// ���� ���� ī�޶� ��Ȳ�� �ʱ�ȭ�ϰ� ī�޶��� ��ġ�� �ʱ� ��ġ��
	// ���� ī�޶� ������ġ�� �ʱ� ��ġ�� �ƴѰ�� ���� Enter���� ��ġ�� �����Ͽ� ��ǥ��ġ�� ���
	CAMERA->SetTargetObj(nullptr);
	CAMERA->SetTargetPos(Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
	Enter();
}

void CScene::SceneUpdate()
{
	// �� ���� �����ص� ������ ���ӿ�����Ʈ�� ����
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		m_listObj[layer].remove_if([](CGameObject* target)
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

	// �� ���� ��� ���ӿ�����Ʈ ��������
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			if (pGameObject->GetReserveDelete())
				pGameObject->SetSafeToDelete();
			else
				pGameObject->GameObjectUpdate();
		}
	}

	// ����� �ڽ� ��������
	Update();
}

void CScene::ScenePhysicsUpdate()
{
	// �� ���� ��� ���ӿ�����Ʈ ����ó�� ����
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectPhysicsUpdate();
		}
	}
}

void CScene::SceneRender()
{
	// �� ���� ��� ���ӿ�����Ʈ ǥ������
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectRender();
		}
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
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectRelease();
			delete pGameObject;
		}
		m_listObj[layer].clear();
	}

	// ����� �ڽ� ������
	Release();
}

list<CGameObject*>& CScene::GetLayerObject(Layer layer)
{
	return m_listObj[(int)layer];
}

void CScene::AddGameObject(CGameObject* pGameObj)
{
	// ���ο� ���ӿ�����Ʈ �߰� �� �ʱ�ȭ
	m_listObj[(int)pGameObj->GetLayer()].push_back(pGameObj);
	pGameObj->GameObjectInit();
}

void CScene::DeleteLayerObject(Layer layer)
{
	for (CGameObject* pObj : m_listObj[(int)layer])
	{
		delete pObj;
	}
	m_listObj[(int)layer].clear();
}

void CScene::DeleteAll()
{
	for (int i = 0; i < (UINT)Layer::Size; i++)
	{
		DeleteLayerObject((Layer)i);
	}
}
