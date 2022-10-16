#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecPos.x -= m_fSpeed * DT;
	}

	if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecPos.x += m_fSpeed * DT;
	}

	if (BUTTONSTAY(VK_UP))
	{
		m_vecPos.y -= m_fSpeed * DT;
	}

	if (BUTTONSTAY(VK_DOWN))
	{
		m_vecPos.y += m_fSpeed * DT;
	}
}

void CPlayer::Render()
{
	RENDER->Rect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);
}

void CPlayer::Release()
{
}
