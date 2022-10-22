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
	CheckLayer(Layer::Monster, Layer::Player);
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

			// 충돌체와 충돌체의 ID 확인
			CCollider* pLeftCollider = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			UINT64 id = CollisionID(pLeftCollider->GetID(), pRightCollider->GetID());

			// 충돌 정보가 없었던 경우, 충돌하지 않은 상태로 보관
			if (m_umapPrevCollision.find(id) == m_umapPrevCollision.end())
				m_umapPrevCollision.insert(make_pair(id, false));
			
			// 충돌처리 확인
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// Prev O, Cur O
				if (m_umapPrevCollision[id])
				{
					// 충돌체 중 하나라도 삭제예정인 경우 충돌 해제
					if (pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete())
					{
						pLeftCollider->OnCollisionExit(pRightCollider);
						pRightCollider->OnCollisionExit(pLeftCollider);
						m_umapPrevCollision[id] = false;
					}
					else
					{
						pLeftCollider->OnCollisionStay(pRightCollider);
						pRightCollider->OnCollisionStay(pLeftCollider);
						m_umapPrevCollision[id] = true;
					}
				}
				// Prev X, Cur O
				else
				{
					// 충돌체 중 하나라도 삭제예정인 경우 충돌시키지 않음
					if (pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete())
					{
						// 아무것도 하지 않음
					}
					else
					{
						pLeftCollider->OnCollisionEnter(pRightCollider);
						pRightCollider->OnCollisionEnter(pLeftCollider);
						m_umapPrevCollision[id] = true;
					}
				}
			}
			else
			{
				// Prev O, Cur X
				if (m_umapPrevCollision[id])
				{
					pLeftCollider->OnCollisionExit(pRightCollider);
					pRightCollider->OnCollisionExit(pLeftCollider);
					m_umapPrevCollision[id] = false;
				}
				// Prev X, Cur X
				else
				{
					m_umapPrevCollision[id] = false;
				}
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

UINT64 CCollisionManager::CollisionID(UINT leftID, UINT rightID)
{
	UINT64 result = 0;
	if (leftID < rightID)
	{
		result |= (UINT64)leftID << 32;
		result |= rightID;
		return result;
	}
	else
	{
		result |= (UINT64)rightID << 32;
		result |= leftID;
		return result;
	}
}
