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

	map<GroupScene, CScene*> m_mapScene;	// 게임씬들을 보관하는 자료구조
	CScene* m_pCurScene;					// 현재 게임씬

	void Init();
	void Update();
	void Render();
	void Release();

public:
	CScene* GetCurScene();					// 현재 게임씬 반환
	void ChangeScene(GroupScene scene);		// 게임씬 변경
};

#define SCENE				CSceneManager::GetInstance()