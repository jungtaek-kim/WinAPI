#pragma once

class CEventManager;
class CScene;

// ���ӿ�����Ʈ : 
// �� ���� �����ϴ� ��ü, ex) ĳ����, �̻���, ����, ������, ��
// ���ӿ�����Ʈ�� ĸ��ȭ�Ͽ� �ൿ�� ǥ���� ������ ���
// �ٸ� ���ӿ�����Ʈ�� ���������� ������ �� ����
class CGameObject
{
	friend CEventManager;
	friend CScene;
protected:
	Vector m_vecPos;	// ���ӿ�����Ʈ�� ��ġ
	Vector m_vecScale;	// ���ӿ�����Ʈ�� ũ��

	bool m_bReservedDelete;		// ���ӿ�����Ʈ�� ������������ ����
	void SetReserveDelete();	// ���ӿ�����Ʈ ���� ����
	bool m_bSafeToDelete;		// ���ӿ�����Ʈ�� �����ص� ���������� ����
	bool GetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� Ȯ��
	void SetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� ǥ��

public:
	CGameObject();
	virtual ~CGameObject();

	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);

	bool GetReserveDelete();		// ���ӿ�����Ʈ�� ������������ Ȯ��

private:
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Update() = 0;		// ���ӿ�����Ʈ�� �ൿ����
	virtual void Render() = 0;		// ���ӿ�����Ʈ�� ǥ������
	virtual void Release() = 0;		// ������
};
