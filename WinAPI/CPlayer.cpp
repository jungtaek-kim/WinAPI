#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCollider.h"

#include "CMissile.h"

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(50, 50);
	m_layer = Layer::Player;
	m_strName = L"플레이어";
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));
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
	RENDER->SetBrush(BrushType::Solid, RGB(255, 0, 0));
	RENDER->Circle(
		m_vecPos.x,
		m_vecPos.y,
		25.f
	);
	RENDER->SetBrush();
}

void CPlayer::Release()
{
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	CHANGESCENE(GroupScene::Score);
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}
