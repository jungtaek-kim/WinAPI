#pragma once
#include "WinAPI.h"

class CCore;
class CCollider;

class CCollisionManager : public SingleTon<CCollisionManager>
{
	friend SingleTon<CCollisionManager>;
	friend CCore;
private:
	CCollisionManager();
	virtual ~CCollisionManager();

	bool m_arrLayer[(int)Layer::Size][(int)Layer::Size];	// 충돌을 확인할 레이어 설정

private:
	void Init();
	void Update();
	void Release();

private:
	void CollisionUpdate(Layer leftLayer, Layer rightLayer);
	bool IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider);

	void CheckLayer(Layer left, Layer right);
	void UnCheckLayer(Layer left, Layer right);
	void ResetCheck();
};

#define COLLISION	CCollisionManager::GetInstance()