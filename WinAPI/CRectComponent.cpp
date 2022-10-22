#include "framework.h"
#include "CRectComponent.h"

#include "CRenderManager.h"
#include "CGameObject.h"

CRectComponent::CRectComponent()
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

CRectComponent::~CRectComponent()
{
}

void CRectComponent::SetOffset(Vector offset)
{
	m_vecOffset = offset;
}

void CRectComponent::SetScale(Vector scale)
{
	m_vecScale = scale;
}

void CRectComponent::SetPenType(PenType type)
{
	m_penType = type;
}

void CRectComponent::SetPenColor(COLORREF color)
{
	m_penColor = color;
}

void CRectComponent::SetPenWidth(int width)
{
	m_penWidth = width;
}

void CRectComponent::SetBrushType(BrushType type)
{
	m_brushType = type;
}

void CRectComponent::SetBrushColor(COLORREF color)
{
	m_brushColor = color;
}

Vector CRectComponent::GetPos()
{
	return m_vecPos;
}

Vector CRectComponent::GetOffset()
{
	return m_vecOffset;
}

Vector CRectComponent::GetScale()
{
	return m_vecScale;
}

PenType CRectComponent::GetPenType()
{
	return m_penType;
}

COLORREF CRectComponent::GetPenColor()
{
	return m_penColor;
}

int CRectComponent::GetPenWidth()
{
	return m_penWidth;
}

BrushType CRectComponent::GetBrushType()
{
	return m_brushType;
}

COLORREF CRectComponent::GetBrushColor()
{
	return m_brushColor;
}

void CRectComponent::Init()
{
}

void CRectComponent::Update()
{
}

void CRectComponent::PhysicsUpdate()
{
	m_vecPos = GetOwner()->GetPos() + m_vecOffset;
}

void CRectComponent::Render()
{
	RENDER->SetPen(m_penType, m_penColor, m_penWidth);
	RENDER->SetBrush(m_brushType, m_brushColor);

	RENDER->Rect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f
	);

	RENDER->SetPen();
	RENDER->SetBrush();
}

void CRectComponent::Release()
{
}
