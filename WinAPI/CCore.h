#pragma once
class CCore : public SingleTon<CCore>
{
	friend SingleTon<CCore>;
private:
	CCore();
	virtual ~CCore();

	HDC m_hdc;
	POINT m_point;

public:
	void Init();		// ���ӽ��۽� �ʱ�ȭ �۾�
	void Update();		// �����Ӹ��� ���ӷ��� ����
	void Render();		// �����Ӹ��� ����ǥ�� ����
	void Release();		// ��������� ������ �۾�
};

#define	CORE	CCore::GetInstance()