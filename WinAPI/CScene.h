#pragma once

class CCore;

class CScene
{
	friend CCore;
public:
	CScene();
	virtual ~CScene();

public:
	// ���������Լ�:
	// �Լ��� �߻�ȭ�Ͽ� ��üȭ���� ���� ��� �ν��Ͻ� ������ ����
	// ���� ��ӹ޾� ���������Լ����� ��üȭ���� ���� �ϼ���Ŵ
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Enter() = 0;		// ����
	virtual void Update() = 0;		// ���ӷ��� ����
	virtual void Render() = 0;		// ����ǥ�� ����
	virtual void Exit() = 0;		// Ż��
	virtual void Release() = 0;		// ������
};
