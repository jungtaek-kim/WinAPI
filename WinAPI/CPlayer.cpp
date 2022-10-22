#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

#include "CMissile.h"

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	AddCollider(Vector(90, 90), Vector(0, 0));
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

	if (BUTTONDOWN(VK_SPACE))
	{
		CreateMissile();
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

void CPlayer::CreateMissile()
{
	Logger::Debug(L"미사일 생성");

	CMissile* pMissile = new CMissile();
	pMissile->SetPos(m_vecPos);
	ADDOBJECT(pMissile);
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	Logger::Debug(L"플레이어가 충돌진입");
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	Logger::Debug(L"플레이어가 충돌중");
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
	Logger::Debug(L"플레이어가 충돌탈출");
}
