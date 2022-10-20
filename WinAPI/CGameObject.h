#pragma once

class CEventManager;
class CScene;
class CComponent;

// ���ӿ�����Ʈ : 
// �� ���� �����ϴ� ��ü, ex) ĳ����, �̻���, ����, ������, ��
// ���ӿ�����Ʈ�� ĸ��ȭ�Ͽ� �ൿ�� ǥ���� ������ ���
// �ٸ� ���ӿ�����Ʈ�� ���������� ������ �� ����
class CGameObject
{
	friend CEventManager;
	friend CScene;
public:
	CGameObject();
	virtual ~CGameObject();

protected:
	Vector m_vecPos;	// ���ӿ�����Ʈ�� ��ġ
	Vector m_vecScale;	// ���ӿ�����Ʈ�� ũ��

public:
	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);

private:
	bool m_bReservedDelete;		// ���ӿ�����Ʈ�� ������������ ����
	bool m_bSafeToDelete;		// ���ӿ�����Ʈ�� �����ص� ���������� ����

	void SetReserveDelete();	// ���ӿ�����Ʈ ���� ����
	bool GetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� Ȯ��
	void SetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� ǥ��
public:
	bool GetReserveDelete();		// ���ӿ�����Ʈ�� ������������ Ȯ��

private:
	list<CComponent*> m_listComponent;	// ������Ʈ���� ������ �ڷᱸ��

	void AddComponent(CComponent* component);		// ������Ʈ �߰�
	void RemoveComponent(CComponent* component);	// ������Ʈ ����

private:
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Update() = 0;		// ���ӿ�����Ʈ�� �ൿ����
	virtual void Render() = 0;		// ���ӿ�����Ʈ�� ǥ������
	virtual void Release() = 0;		// ������
};
