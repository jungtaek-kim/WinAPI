#pragma once
#include "WinAPI.h"

class CCore;
class CScene;

class CSceneManager : public SingleTon<CSceneManager>
{
	friend class SingleTon<CSceneManager>;
	friend class CCore;
private:
	CSceneManager();
	virtual ~CSceneManager();

	map<GroupScene, CScene*> m_mapScene;	// ���Ӿ����� �����ϴ� �ڷᱸ��
	CScene* m_pCurScene;					// ���� ���Ӿ�

	void Init();
	void Update();
	void Render();
	void Release();

public:
	CScene* GetCurScene();					// ���� ���Ӿ� ��ȯ
	void ChangeScene(GroupScene scene);		// ���Ӿ� ����
};

#define SCENE				CSceneManager::GetInstance()