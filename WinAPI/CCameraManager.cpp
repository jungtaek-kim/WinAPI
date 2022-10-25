#include "framework.h"
#include "CCameraManager.h"

#include "CGameObject.h"

CCameraManager::CCameraManager()
{
	m_vecLookAt		= Vector(0, 0);
	m_vecTargetPos	= Vector(0, 0);
	m_pTargetObj	= nullptr;
}

CCameraManager::~CCameraManager()
{
}

Vector CCameraManager::GetLookAt()
{
	return m_vecLookAt;
}

Vector CCameraManager::GetTargetPos()
{
	return m_vecTargetPos;
}

CGameObject* CCameraManager::GetTargetObj()
{
	return m_pTargetObj;
}

void CCameraManager::SetTargetPos(Vector targetPos)
{
	m_vecTargetPos = targetPos;
}

void CCameraManager::SetTargetObj(CGameObject* pTargetObj)
{
	m_pTargetObj = pTargetObj;
}

void CCameraManager::Init()
{
}

void CCameraManager::Update()
{
	// 추적할 게임오브젝트가 있을 경우
	if (nullptr != m_pTargetObj)
	{
		if (m_pTargetObj->GetReserveDelete())
		{
			// 추적할 게임오브젝트가 삭제예정인 경우 추적 해제
			m_pTargetObj = nullptr;
		}
		else
		{
			// 추적할 게임오브젝트가 있을 경우 게임오브젝트의 위치를 목표위치로 지정
			SetTargetPos(m_pTargetObj->GetPos());
		}
	}

	// 목표 위치로 이동
	MoveToTarget();
}

void CCameraManager::Release()
{
}

void CCameraManager::MoveToTarget()
{
	m_vecLookAt = m_vecTargetPos;
}
