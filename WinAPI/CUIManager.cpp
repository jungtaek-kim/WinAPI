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

void CUIManager::MouseEvent(CUI* pUI)
{
	if (pUI->m_bCurMouseOn)
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
}

void CUIManager::Init()
{
}

void CUIManager::Update()
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];

	for (CGameObject* pGameObject : listUI)
	{
		CUI* pUI = dynamic_cast<CUI*>(pGameObject);
		MouseEvent(pUI);
	}
}

void CUIManager::Release()
{
}
