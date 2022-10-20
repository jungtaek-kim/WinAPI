#include "framework.h"
#include "CCollider.h"

#include "CRenderManager.h"
#include "CGameObject.h"

CCollider::CCollider()
{
	m_vecPos = Vector(0, 0);
	m_vecOffsetPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
}

CCollider::~CCollider()
{
}

Vector CCollider::GetPos()
{
	return m_vecPos;
}

void CCollider::SetPos(Vector pos)
{
	m_vecPos = pos;
}

Vector CCollider::GetOffsetPos()
{
	return m_vecOffsetPos;
}

void CCollider::SetOffsetPos(Vector offset)
{
	m_vecOffsetPos = offset;
}

Vector CCollider::GetScale()
{
	return m_vecScale;
}

void CCollider::SetScale(Vector scale)
{
	m_vecScale = scale;
}

void CCollider::Init()
{
}

void CCollider::Update()
{
}

void CCollider::PhysicsUpdate()
{
	m_vecPos = m_vecOffsetPos + GetOwner()->GetPos();
}

void CCollider::Render()
{
	RENDER->SetPen(PenType::Solid, RGB(0, 255, 0));
	RENDER->SetBrush(BrushType::Null);

	RENDER->Rect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);

	RENDER->SetPen();
	RENDER->SetBrush();
}

void CCollider::Release()
{
}

void CCollider::OnCollision(CCollider* pOtherCollider)
{
	Logger::Debug(L"Ãæµ¹ÇÔ!");
}