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
				// �浹 Ȯ�� ����
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
		// �浹ü ������Ʈ�� ���� ��� ����
		if (nullptr == pLeftObj->GetCollider())
			continue;

		for (CGameObject* pRightObj : rightListObj)
		{
			// �浹ü ������Ʈ�� ���� ��� ����
			if (nullptr == pRightObj->GetCollider())
				continue;

			// �ڱ� �ڽŰ��� �浹�� ����
			if (pLeftObj == pRightObj)
				continue;

			// �浹ü�� �浹ü�� ID Ȯ��
			CCollider* pLeftCollider = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			UINT64 id = CollisionID(pLeftCollider->GetID(), pRightCollider->GetID());

			// �浹 ������ ������ ���, �浹���� ���� ���·� ����
			if (m_umapPrevCollision.find(id) == m_umapPrevCollision.end())
				m_umapPrevCollision.insert(make_pair(id, false));
			
			// �浹ó�� Ȯ��
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// Prev O, Cur O
				if (m_umapPrevCollision[id])
				{
					// �浹ü �� �ϳ��� ���������� ��� �浹 ����
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
					// �浹ü �� �ϳ��� ���������� ��� �浹��Ű�� ����
					if (pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete())
					{
						// �ƹ��͵� ���� ����
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
	// �簢 �浹
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
	// memset(�����ּ�, ������ ������, ������ ũ��) : �޸� �ʱ�ȭ �Լ�
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
