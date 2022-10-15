#pragma once
class CCore : public SingleTon<CCore>
{
	friend SingleTon<CCore>;
private:
	CCore();
	virtual ~CCore();

	float m_pointX;
	float m_pointY;

public:
	void Init();		// ���ӽ��۽� �ʱ�ȭ �۾�
	void Update();		// �����Ӹ��� ���ӷ��� ����
	void Render();		// �����Ӹ��� ����ǥ�� ����
	void Release();		// ��������� ������ �۾�
};

#define	CORE	CCore::GetInstance()