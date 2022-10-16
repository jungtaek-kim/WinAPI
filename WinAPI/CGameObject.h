#pragma once

class CScene;

// ���ӿ�����Ʈ : 
// �� ���� �����ϴ� ��ü, ex) ĳ����, �̻���, ����, ������, ��
// ���ӿ�����Ʈ�� ĸ��ȭ�Ͽ� �ൿ�� ǥ���� ������ ���
// �ٸ� ���ӿ�����Ʈ�� ���������� ������ �� ����
class CGameObject
{
	friend CScene;
protected:
	Vector m_vecPos;	// ���ӿ�����Ʈ�� ��ġ
	Vector m_vecScale;	// ���ӿ�����Ʈ�� ũ��

public:
	CGameObject();
	virtual ~CGameObject();

	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);

private:
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Update() = 0;		// ���ӿ�����Ʈ�� �ൿ����
	virtual void Render() = 0;		// ���ӿ�����Ʈ�� ǥ������
	virtual void Release() = 0;		// ������
};
