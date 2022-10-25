#include "framework.h"
#include "CCameraManager.h"

#include "CTimeManager.h"
#include "CGameObject.h"

CCameraManager::CCameraManager()
{
	m_vecLookAt		= Vector(0, 0);
	m_vecTargetPos	= Vector(0, 0);
	m_pTargetObj	= nullptr;
	m_fTimeToTarget = 0;
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

void CCameraManager::SetTargetPos(Vector targetPos, float timeToTarget)
{
	m_vecTargetPos = targetPos;
	m_fTimeToTarget = timeToTarget;
}

void CCameraManager::SetTargetObj(CGameObject* pTargetObj)
{
	m_pTargetObj = pTargetObj;
}

Vector CCameraManager::WorldToScreenPoint(Vector worldPoint)
{
	return worldPoint - (m_vecLookAt - Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
}

Vector CCameraManager::ScreenToWorldPoint(Vector screenPoint)
{
	return screenPoint + (m_vecLookAt - Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
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
	m_fTimeToTarget -= DT;

	if (m_fTimeToTarget <= 0)
	{
		// ��ǥ��ġ���� ���� �ð��� ���� ��� �������� ������ġ ����
		m_vecLookAt = m_vecTargetPos;
	}
	else
	{
		// ��ǥ��ġ���� ���� �ð��� ���� ���
		// ���������� �����ð���ŭ�� �ӵ��� �̵�
		// �̵��Ÿ� = �ӷ� * �ð�
		// �ӷ� = (������ - �����) / �ҿ�ð�
		// �ð� = �����Ӵ����ð�
		m_vecLookAt += (m_vecTargetPos - m_vecLookAt) / m_fTimeToTarget * DT;
	}
}
