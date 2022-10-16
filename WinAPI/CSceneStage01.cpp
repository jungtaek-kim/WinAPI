#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"

CSceneStage01::CSceneStage01()
{
	m_pointX = 0;
	m_pointY = 0;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	m_pointX = WINSIZEX * 0.5f;
	m_pointY = WINSIZEY * 0.5f;
}

void CSceneStage01::Enter()
{
}

void CSceneStage01::Update()
{
	if (BUTTONSTAY(VK_LEFT))
	{
		m_pointX -= 100 * DT;
	}

	if (BUTTONSTAY(VK_RIGHT))
	{
		m_pointX += 100 * DT;
	}

	if (BUTTONSTAY(VK_UP))
	{
		m_pointY -= 100 * DT;
	}

	if (BUTTONSTAY(VK_DOWN))
	{
		m_pointY += 100 * DT;
	}
}

void CSceneStage01::Render()
{
	RENDER->Rect(m_pointX - 50, m_pointY - 50, m_pointX + 50, m_pointY + 50);
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
