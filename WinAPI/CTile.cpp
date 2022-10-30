#include "framework.h"
#include "CTile.h"

#include "CRenderManager.h"
#include "CResourceManager.h"
#include "CImage.h"

CTile::CTile()
{
	m_pImage = nullptr;

	m_uiTilePosX = 0;
	m_uiTilePosY = 0;
	m_uiTileIndex = 0;

	m_bLineRender = false;

	m_strName = L"Tile";
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(TILESIZE, TILESIZE);
	m_layer = Layer::Tile;
}

CTile::~CTile()
{
}

void CTile::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Tile", L"Image\\Tile.png");
	m_uiImageXCount = m_pImage->GetWidth() / TILESIZE;
	m_uiImageYCount = m_pImage->GetHeight() / TILESIZE;
}

void CTile::Update()
{
}

void CTile::Render()
{
	int tileIndexX = (m_uiTileIndex % m_uiImageXCount);
	int tileIndexY = (m_uiTileIndex / m_uiImageYCount);

	RENDER->FrameImage(
		m_pImage,
		m_vecPos.x,
		m_vecPos.y,
		m_vecPos.x + m_vecScale.x,
		m_vecPos.y + m_vecScale.y,
		(float)(tileIndexX * TILESIZE),
		(float)(tileIndexY * TILESIZE),
		(float)((tileIndexX + 1) * TILESIZE),
		(float)((tileIndexY + 1) * TILESIZE)
	);

	if (m_bLineRender)
	{
		RENDER->FrameRect(
			m_vecPos.x,
			m_vecPos.y,
			m_vecPos.x + m_vecScale.x,
			m_vecPos.y + m_vecScale.y
		);
	}
}

void CTile::Release()
{
}

void CTile::SetTilePosX(UINT x)
{
	m_uiTilePosX = x;
	m_vecPos.x = (float)(x * TILESIZE);
}

void CTile::SetTilePosY(UINT y)
{
	m_uiTilePosY = y;
	m_vecPos.y = (float)(y * TILESIZE);
}

void CTile::SetTilePos(UINT x, UINT y)
{
	m_uiTilePosX = x;
	m_uiTilePosY = y;
	m_vecPos.x = (float)(x * TILESIZE);
	m_vecPos.y = (float)(y * TILESIZE);
}

void CTile::SetTileIndex(UINT index)
{
	m_uiTileIndex = index;
}

void CTile::SetLineRender(bool line)
{
	m_bLineRender = line;
}

int CTile::GetTilePosX()
{
    return m_uiTilePosX;
}

int CTile::GetTilePosY()
{
    return m_uiTilePosY;
}

int CTile::GetTileIndex()
{
    return m_uiTileIndex;
}

bool CTile::GetLineRender()
{
	return m_bLineRender;
}
