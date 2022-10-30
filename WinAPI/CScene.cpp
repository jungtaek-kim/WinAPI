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
	// 씬 내에 모든 게임오브젝트 초기화
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectInit();
		}
	}

	// 상속한 자식 초기화
	Init();
}

void CScene::SceneEnter()
{
	// 이전 씬의 카메라 상황을 초기화하고 카메라의 위치를 초기 위치로
	// 씬의 카메라 시작위치가 초기 위치가 아닌경우 씬의 Enter에서 위치를 설정하여 목표위치가 덮어씀
	CAMERA->SetTargetObj(nullptr);
	CAMERA->SetTargetPos(Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
	Enter();
}

void CScene::SceneUpdate()
{
	// 씬 내에 삭제해도 안전한 게임오브젝트를 삭제
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

	// 씬 내에 모든 게임오브젝트 로직갱신
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

	// 상속한 자식 로직갱신
	Update();
}

void CScene::ScenePhysicsUpdate()
{
	// 씬 내에 모든 게임오브젝트 물리처리 진행
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
	// 씬 내에 모든 게임오브젝트 표현갱신
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectRender();
		}
	}

	// 상속한 자식 표현갱신
	Render();
}

void CScene::SceneExit()
{
	Exit();
}

void CScene::SceneRelease()
{
	// 씬 내에 모든 게임오브젝트 마무리
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectRelease();
			delete pGameObject;
		}
		m_listObj[layer].clear();
	}

	// 상속한 자식 마무리
	Release();
}

list<CGameObject*>& CScene::GetLayerObject(Layer layer)
{
	return m_listObj[(int)layer];
}

void CScene::AddGameObject(CGameObject* pGameObj)
{
	// 새로운 게임오브젝트 추가 및 초기화
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
