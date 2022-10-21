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

			CCollider* pLeftCollider = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			// �浹ó�� Ȯ��
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
