#include "framework.h"
#include "CEllipseComponent.h"

#include "CRenderManager.h"
#include "CGameObject.h"

CEllipseComponent::CEllipseComponent()
{
	m_vecPos = Vector(0, 0);
	m_vecOffset = Vector(0, 0);
	m_vecScale = Vector(100, 100);

	m_penType = PenType::Solid;
	m_penWidth = 1;
	m_penColor = RGB(0, 0, 0);

	m_brushType = BrushType::Null;
	m_brushColor = RGB(255, 255, 255);
}

CEllipseComponent::~CEllipseComponent()
{
}

void CEllipseComponent::SetOffset(Vector offset)
{
	m_vecOffset = offset;
}

void CEllipseComponent::SetScale(Vector scale)
{
	m_vecScale = scale;
}

void CEllipseComponent::SetRadius(float radius)
{
	m_vecScale = Vector(radius * 2, radius * 2);
}

void CEllipseComponent::SetPenType(PenType type)
{
	m_penType = type;
}

void CEllipseComponent::SetPenColor(COLORREF color)
{
	m_penColor = color;
}

void CEllipseComponent::SetPenWidth(int width)
{
	m_penWidth = width;
}

void CEllipseComponent::SetBrushType(BrushType type)
{
	m_brushType = type;
}

void CEllipseComponent::SetBrushColor(COLORREF color)
{
	m_brushColor = color;
}

Vector CEllipseComponent::GetPos()
{
	return m_vecPos;
}

Vector CEllipseComponent::GetOffset()
{
	return m_vecOffset;
}

Vector CEllipseComponent::GetScale()
{
	return m_vecScale;
}

PenType CEllipseComponent::GetPenType()
{
	return m_penType;
}

COLORREF CEllipseComponent::GetPenColor()
{
	return m_penColor;
}

int CEllipseComponent::GetPenWidth()
{
	return m_penWidth;
}

BrushType CEllipseComponent::GetBrushType()
{
	return m_brushType;
}

COLORREF CEllipseComponent::GetBrushColor()
{
	return m_brushColor;
}

void CEllipseComponent::Init()
{
}

void CEllipseComponent::Update()
{
}

void CEllipseComponent::PhysicsUpdate()
{
	m_vecPos = GetOwner()->GetPos() + m_vecOffset;
}

void CEllipseComponent::Render()
{
	RENDER->SetPen(m_penType, m_penColor, m_penWidth);
	RENDER->SetBrush(m_brushType, m_brushColor);

	RENDER->Ellipse(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f
	);

	RENDER->SetPen();
	RENDER->SetBrush();
}

void CEllipseComponent::Release()
{
}