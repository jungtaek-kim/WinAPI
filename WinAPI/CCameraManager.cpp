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
	// ������ ���ӿ�����Ʈ�� ���� ���
	if (nullptr != m_pTargetObj)
	{
		if (m_pTargetObj->GetReserveDelete())
		{
			// ������ ���ӿ�����Ʈ�� ���������� ��� ���� ����
			m_pTargetObj = nullptr;
		}
		else
		{
			// ������ ���ӿ�����Ʈ�� ���� ��� ���ӿ�����Ʈ�� ��ġ�� ��ǥ��ġ�� ����
			SetTargetPos(m_pTargetObj->GetPos());
		}
	}

	// ��ǥ ��ġ�� �̵�
	MoveToTarget();
}

void CCameraManager::Release()
{
}

void CCameraManager::MoveToTarget()
{
	m_vecLookAt = m_vecTargetPos;
}
