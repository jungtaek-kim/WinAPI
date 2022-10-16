#include "framework.h"
#include "CSceneManager.h"

#include "CScene.h"
#include "CSceneTitle.h"
#include "CSceneStage01.h"

CSceneManager::CSceneManager()
{
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Init()
{
	// TODO : 게임에 필요한 씬 추가
	// 게임씬들을 자료구조에 추가
	CScene* pSceneTitle = new CSceneTitle();
	m_mapScene.insert(make_pair(GroupScene::Title, pSceneTitle));
	CScene* pSceneStage01 = new CSceneStage01();
	m_mapScene.insert(make_pair(GroupScene::Stage01, pSceneStage01));

	// 게임씬 자료구조를 순회하며 씬을 초기화
	map<GroupScene, CScene*>::iterator iter;
	for (iter = m_mapScene.begin();
		iter != m_mapScene.end();
		iter++)
	{
		iter->second->Init();
	}

	// 가장 처음으로 진행해야할 게임씬 시작
	m_pCurScene = pSceneTitle;
	m_pCurScene->Enter();
}

void CSceneManager::Update()
{
	m_pCurScene->Update();
}

void CSceneManager::Render()
{
	m_pCurScene->Render();
}

void CSceneManager::Release()
{
	// 게임씬 자료구조를 순회하며 동적할당된 씬을 제거
	map<GroupScene, CScene*>::iterator iter;
	for (iter = m_mapScene.begin();
		iter != m_mapScene.end();
		iter++)
	{
		iter->second->Release();
		delete iter->second;
	}
	// 모든 동적할당된 씬을 제거한뒤 자료구조를 clear
	m_mapScene.clear();
}

void CSceneManager::ChangeScene(GroupScene scene)
{
	// 이전씬을 Exit, 다음씬을 Enter
	m_pCurScene->Exit();
	m_pCurScene = m_mapScene[scene];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
