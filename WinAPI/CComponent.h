#pragma once

class CGameObject;

// ���������� ������Ʈ - ������Ʈ : 
// ���α׷��ֿ� �־� ��� ������ ������ ������ ������ ���
// ��ü�� ������ ��� ������ ����� ���������� �����ϴ� ������ ���
// ����� ��� ��� ����ϴ� �ڽĿ��� �ݵ�� ����� ���Ե�����
// ������Ʈ�� ��� �ʿ��� ��ü���� ���������� ���� �� ����
class CComponent
{
	friend CGameObject;
public:
	CComponent();
	virtual ~CComponent();

private:
	CGameObject* m_pOwner;

protected:
	int m_iZOrder;		// ������Ʈ�� ���ļ�����

private:
	void SetOwner(CGameObject* pOwner);

protected:
	void SetZOrder(int zOrder);

public:
	CGameObject* GetOwner();
	int GetZOrder();

private:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PhysicsUpdate(){};		// ����ó���� �ʿ��� ������Ʈ�� �������Ͽ� ���
	virtual void Render() = 0;
	virtual void Release() = 0;
};

