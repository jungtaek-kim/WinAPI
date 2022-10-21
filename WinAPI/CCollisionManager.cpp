#include "framework.h"
#include "CCollisionManager.h"

#include "CSceneManager.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
{
	m_arrLayer[0][0] = { 0 };
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
	CheckLayer(Layer::Monster, Layer::Missile);
}

void CCollisionManager::Update()
{
	for (int left = 0; left < (int)Layer::Size; left++)
	{
		for (int right = left; right < (int)Layer::Size; right++)
		{
			if (m_arrLayer[left][right])
			{
				// 충돌 확인 진행
				CollisionUpdate((Layer)left, (Layer)right);
			}
		}
	}
}

void CCollisionManager::Release()
{
}

void CCollisionManager::CollisionUpdate(Layer leftLayer, Layer rightLayer)
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& leftListObj = pCurScene->m_listObj[(int)leftLayer];
	const list<CGameObject*>& rightListObj = pCurScene->m_listObj[(int)rightLayer];

	for (CGameObject* pLeftObj : leftListObj)
	{
		// 충돌체 컴포넌트가 없는 경우 무시
		if (nullptr == pLeftObj->GetCollider())
			continue;

		for (CGameObject* pRightObj : rightListObj)
		{
			// 충돌체 컴포넌트가 없는 경우 무시
			if (nullptr == pRightObj->GetCollider())
				continue;

			// 자기 자신과의 충돌은 무시
			if (pLeftObj == pRightObj)
				continue;

			CCollider* pLeftCollider = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			// 충돌처리 확인
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				pLeftCollider->OnCollision(pRightCollider);
				pRightCollider->OnCollision(pLeftCollider);
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider)
{
	// 사각 충돌
	Vector vecLeftPos = pLeftCollider->GetPos();
	Vector vecLeftScale = pLeftCollider->GetScale();
	
	Vector vecRightPos = pRightCollider->GetPos();
	Vector vecRightScale = pRightCollider->GetScale();

	if (abs(vecLeftPos.x - vecRightPos.x) < (vecLeftScale.x + vecRightScale.x) / 2.f
		&& abs(vecLeftPos.y - vecRightPos.y) < (vecLeftScale.y + vecRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionManager::CheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = true;
	m_arrLayer[(int)right][(int)left] = true;
}

void CCollisionManager::UnCheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = false;
	m_arrLayer[(int)right][(int)left] = false;
}

void CCollisionManager::ResetCheck()
{
	// memset(시작주소, 설정할 데이터, 설정할 크기) : 메모리 초기화 함수
	memset(m_arrLayer, 0, sizeof(bool) * (int)Layer::Size * (int)Layer::Size);
	/*
	for (bool check : m_arrCheckLayer)
	{
		check = false;
	}
	*/
}
