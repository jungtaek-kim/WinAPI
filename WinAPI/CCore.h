#pragma once

class CScene;

class CCore : public SingleTon<CCore>
{
	friend SingleTon<CCore>;
private:
	CCore();
	virtual ~CCore();

	CScene* pCurScene;
	CScene* pSceneTitle;
	CScene* pSceneStage01;

public:
	void Init();		// ���ӽ��۽� �ʱ�ȭ �۾�
	void Update();		// �����Ӹ��� ���ӷ��� ����
	void Render();		// �����Ӹ��� ����ǥ�� ����
	void Release();		// ��������� ������ �۾�
};

#define	CORE	CCore::GetInstance()