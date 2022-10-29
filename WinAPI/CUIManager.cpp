#include "framework.h"
#include "CUIManager.h"

#include "CSceneManager.h"
#include "CInputManager.h"

#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

CUI* CUIManager::GetTopUI()
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];

	// 가장 위에 있는 UI는 씬의 게임오브젝트 자료구조에서 차례대로 순회하며 Render 한다는 것을 이용하여
	// 가장 마지막에 있는 게임오브젝트가 제일 위에 있는 게임오브젝트
	// 역방향 반복자 : 가장 뒤의 요소부터 역순으로 순회
	for (auto iter = listUI.rbegin(); iter != listUI.rend(); iter++)
	{
		// 역순으로 순회 중 가장먼저 마우스가 올려져 있는 UI가 마우스 클릭의 대상
		CUI* pUI = static_cast<CUI*>(*iter);
		if (pUI->m_bCurMouseOn)
		{
			return pUI;
		}
	}

	return nullptr;
}

CUI* CUIManager::GetTopChildUI(CUI* pUI)
{
	if (nullptr == pUI)
		return nullptr;

	queue<CUI*> queueUI;
	CUI* pTargetUI = nullptr;

	// BFS 을 통해서 UI중 마우스가 올라간 가장 자식 UI 확인
	queueUI.push(pUI);
	while (!queueUI.empty())
	{
		CUI* pUI = queueUI.front();
		queueUI.pop();

		if (pUI->m_bCurMouseOn)
		{
			pTargetUI = pUI;
		}

		for (CUI* pChildUI : pUI->m_listChildUI)
		{
			queueUI.push(pChildUI);
		}
	}

	return pTargetUI;
}

void CUIManager::MouseEvent(CUI* pUI, CUI* pTopChildUI)
{
	if (pUI->m_bCurMouseOn && pUI == pTopChildUI)
	{
		pUI->OnMouseOver();
		if (!pUI->m_bPrevMouseOn)
		{
			pUI->OnMouseEnter();
			pUI->m_bPrevMouseOn = true;
		}

		if (BUTTONDOWN(VK_LBUTTON))
		{
			pUI->OnMouseDown();
			pUI->m_bPrevDown = true;
		}
		else if (BUTTONUP(VK_LBUTTON))
		{
			pUI->OnMouseUp();

			if (pUI->m_bPrevDown)
			{
				pUI->OnMouseClicked();
			}
			pUI->m_bPrevDown = false;
		}
	}
	else
	{
		if (pUI->m_bPrevMouseOn)
		{
			pUI->OnMouseExit();
			pUI->m_bPrevMouseOn = false;
		}
		if (BUTTONUP(VK_LBUTTON))
		{
			pUI->m_bPrevDown = false;
		}
	}

	for (CUI* pChildUI : pUI->m_listChildUI)
	{
		MouseEvent(pChildUI, pTopChildUI);
	}
}

void CUIManager::Init()
{
}

void CUIManager::Update()
{
	CUI* pTopUI = GetTopUI();
	CUI* pTopChildUI = GetTopChildUI(pTopUI);

	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];

	for (CGameObject* pGameObject : listUI)
	{
		CUI* pUI = dynamic_cast<CUI*>(pGameObject);
		MouseEvent(pUI, pTopChildUI);
	}
}

void CUIManager::Release()
{
}
