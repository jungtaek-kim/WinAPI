#include "framework.h"
#include "CSceneTileTool.h"

#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

#include "CTile.h"

CSceneTileTool::CSceneTileTool()
{
	m_iTileSizeX = 0;
	m_iTileSizeY = 0;
	m_fScrollSpeed = 300;
}

CSceneTileTool::~CSceneTileTool()
{
}

void CSceneTileTool::CreateTiles(UINT sizeX, UINT sizeY)
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

void CSceneTileTool::SetTileIndex(UINT index)
{
	Vector vecMousePos = MOUSEWORLDPOS;
	float tilePosX = vecMousePos.x / CTile::TILESIZE;
	float tilePosY = vecMousePos.y / CTile::TILESIZE;

	// 타일이 없는 위치일 경우 무시
	if (tilePosX < 0.f || (int)m_iTileSizeX <= tilePosX ||
		tilePosY < 0.f || (int)m_iTileSizeY <= tilePosY)
		return;

	const list<CGameObject*>& listTile = GetLayerObject(Layer::Tile);
	for (CGameObject* pGameObject : listTile)
	{
		CTile* pTile = dynamic_cast<CTile*>(pGameObject);
		if (pTile->GetTilePosX() != (int)tilePosX ||
			pTile->GetTilePosY() != (int)tilePosY)
			continue;

		pTile->SetTileIndex(pTile->GetTileIndex() + index);
		return;
	}
}

void CSceneTileTool::CameraMove()
{
	Vector dir;
	if (BUTTONSTAY('A'))
	{
		dir.x = -1;
	}
	else if (BUTTONSTAY('D'))
		dir.x = 1;
	else dir.x = 0;

	if (BUTTONSTAY('W'))
		dir.y = -1;
	else if (BUTTONSTAY('S'))
		dir.y = 1;
	else
		dir.y = 0;

	CAMERA->Scroll(dir, m_fScrollSpeed);
}

void CSceneTileTool::Init()
{
	CTile* pTile1 = new CTile;
	pTile1->SetTileIndex(1);
	pTile1->SetTilePos(1, 1);
	AddGameObject(pTile1);
}

void CSceneTileTool::Enter()
{
	CreateTiles(10, 10);
}

void CSceneTileTool::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GroupScene::Title);
	}

	if (LMOUSEDOWN(false))
	{
		SetTileIndex(1);
	}

	CameraMove();
}

void CSceneTileTool::Render()
{
}

void CSceneTileTool::Exit()
{
	DeleteAll();
}

void CSceneTileTool::Release()
{
}
