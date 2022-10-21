#pragma once
#include "WinAPI.h"

class CCore;
class CEventManager;
class CCollisionManager;
class CScene;

class CSceneManager : public SingleTon<CSceneManager>
{
	friend class SingleTon<CSceneManager>;
	friend class CCore;
	friend class CEventManager;
	friend class CCollisionManager;
private:
	CSceneManager();
	virtual ~CSceneManager();

	map<GroupScene, CScene*> m_mapScene;	// ���Ӿ����� �����ϴ� �ڷᱸ��
	CScene* m_pCurScene;					// ���� ���Ӿ�

	void Init();
	void Update();
	void Render();
	void Release();

	CScene* GetCurScene();					// ���� ���Ӿ� ��ȯ
	void ChangeScene(GroupScene scene);		// ���Ӿ� ����
};

#define SCENE				CSceneManager::GetInstance()