#pragma once

class CCore;
class CGameObject;

class CCameraManager : public SingleTon<CCameraManager>
{
	friend SingleTon<CCameraManager>;
	friend CCore;
private:
	CCameraManager();
	virtual ~CCameraManager();

private:
	Vector			m_vecLookAt;	// ī�޶� ���� �����ִ� ��ġ
	Vector			m_vecTargetPos;	// ī�޶��� ��ǥ ��ġ
	CGameObject*	m_pTargetObj;	// ī�޶� ������ ������Ʈ

public:
	Vector			GetLookAt();
	Vector			GetTargetPos();
	CGameObject*	GetTargetObj();

	// ������Ʈ�� ������ ��� ��ǥ��ġ�� ��ǥ ������Ʈ�� ��ġ�� ������
	void SetTargetPos(Vector targetPos);		// ī�޶��� ��ǥ ��ġ ����
	void SetTargetObj(CGameObject* pTargetObj);	// ī�޶��� ��ǥ ������Ʈ ����

	Vector WorldToScreenPoint(Vector worldPoint);	// ������ġ->ȭ����ġ
	Vector ScreenToWorldPoint(Vector screenPoint);	// ȭ����ġ->������ġ

private:
	void Init();
	void Update();
	void Release();

private:
	void MoveToTarget();
};

#define CAMERA	CCameraManager::GetInstance()