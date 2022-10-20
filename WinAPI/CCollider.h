#pragma once
#include "CComponent.h"

class CGameObject;

class CCollider : public CComponent
{
	friend CGameObject;

public:
	CCollider();
	virtual ~CCollider();

private:
	Vector m_vecPos;		// �浹ü�� ��ġ
	Vector m_vecOffsetPos;	// �浹ü�� ������(������)
	Vector m_vecScale;		// �浹ü�� ũ��

private:
	void SetPos(Vector pos);
	void SetOffsetPos(Vector offset);
	void SetScale(Vector scale);

public:
	Vector GetPos();
	Vector GetOffsetPos();
	Vector GetScale();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	// �浹 ���� �Լ�
private:
	void OnCollision(CCollider* pOtherCollider);	// �浹��
};

