#pragma once

class CSceneManager;
class CEventManager;
class CGameObject;

class CScene
{
	friend CSceneManager;
	friend CEventManager;
private:
	list<CGameObject*> m_listObj;

public:
	CScene();
	virtual ~CScene();

private:
	// �� �θ� ���� �Լ��� :
	// ���� �ִ� ��� ���ӿ�����Ʈ���� ����
	void SceneInit();
	void SceneEnter();
	void SceneUpdate();
	void ScenePhysicsUpdate();
	void SceneRender();
	void SceneExit();
	void SceneRelease();

	// ���������Լ�:
	// �Լ��� �߻�ȭ�Ͽ� ��üȭ���� ���� ��� �ν��Ͻ� ������ ����
	// ���� ��ӹ޾� ���������Լ����� ��üȭ���� ���� �ϼ���Ŵ
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Enter() = 0;		// ����
	virtual void Update() = 0;		// ���ӷ��� ����
	virtual void Render() = 0;		// ����ǥ�� ����
	virtual void Exit() = 0;		// Ż��
	virtual void Release() = 0;		// ������

protected:
	void AddGameObject(CGameObject* pGameObj);
	// ���������� ���ӿ�����Ʈ �ڷᱸ������ ������ ���ӿ�����Ʈ�� ã�Ƽ� �����ϴ� ����� ä������ ����
	// 1. ���ӿ�����Ʈ�� Ž���Ͽ� �����ϴ� ���� ��ȿ����
	// 2. ���������� ���ӿ�����Ʈ�� �����ϰ� �ִ� ���ӿ�����Ʈ�鿡�� �����ð��� �����
	// -> Update ������ ���������� ������Ʈ�� �������Ӹ� �����ϰ� ������������ ���۵� �� ������
	// void DeleteGameObject(CGameObject* pGameObj);
};
