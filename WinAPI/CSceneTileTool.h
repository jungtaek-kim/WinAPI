#pragma once
#include "CScene.h"
class CSceneTileTool : public CScene
{
public:
	CSceneTileTool();
	virtual ~CSceneTileTool();

private:
	UINT m_iTileSizeX;
	UINT m_iTileSizeY;

	float m_fScrollSpeed;

private:
	void CreateTiles(UINT sizeX, UINT sizeY);
	void SetTileIndex(UINT index);

	void CameraMove();

private:
	void Init() override;
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
	void Release() override;
};

