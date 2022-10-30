#include "framework.h"
#include "CScene.h"

#include "CCameraManager.h"
#include "CGameObject.h"
#include "CTile.h"

CScene::CScene()
{
	m_iTileSizeX = 0;
	m_iTileSizeY = 0;
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
		if ((int)Layer::Tile == layer)
		{
			TileRender();
			continue;
		}
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

void CScene::TileRender()
{
	// ���� ȭ�鿡 ǥ�õ��� �ʴ� Ÿ���� �������� �������� ����
	Vector vecCamLook = CAMERA->GetLookAt();
	Vector vecLeftTop = vecCamLook - Vector(WINSIZEX, WINSIZEY) / 2.f;

	int iLTX = (int)vecLeftTop.x / CTile::TILESIZE;
	int iLTY = (int)vecLeftTop.y / CTile::TILESIZE;
	int iRBX = (int)WINSIZEX / CTile::TILESIZE;
	int iRBY = (int)WINSIZEY / CTile::TILESIZE;

	for (CGameObject* pGameObject : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = (CTile*)pGameObject;
		if (pTile->GetTilePosX() > iLTX - 5 && pTile->GetTilePosX() < iLTX + iRBX + 5 &&
			pTile->GetTilePosY() > iLTY - 5 && pTile->GetTilePosY() < iLTY + iRBY + 5)
			pTile->Render();
	}
}

void CScene::CreateTiles(UINT sizeX, UINT sizeY)
{
	DeleteLayerObject(Layer::Tile);

	m_iTileSizeX = sizeX;
	m_iTileSizeY = sizeY;
	for (UINT y = 0; y < sizeY; y++)
	{
		for (UINT x = 0; x < sizeX; x++)
		{
			CTile* pTile = new CTile();
			pTile->SetTilePos(x, y);
			pTile->SetLineRender(true);
			AddGameObject(pTile);
		}
	}
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
