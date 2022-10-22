#include "framework.h"
#include "CTextComponent.h"

#include "CRenderManager.h"
#include "CGameObject.h"

CTextComponent::CTextComponent()
{
	m_strText = L"";
	m_vecPos = Vector(0, 0);
	m_vecOffset = Vector(0, 0);
}

CTextComponent::~CTextComponent()
{
}

void CTextComponent::SetType(TextType type)
{
	m_type = type;
}

void CTextComponent::SetText(wstring text)
{
	m_strText = text;
}

void CTextComponent::SetOffset(Vector offset)
{
	m_vecOffset = offset;
}

TextType CTextComponent::GetType()
{
	return m_type;
}

const wstring& CTextComponent::GetText()
{
	return m_strText;
}

Vector CTextComponent::GetPos()
{
	return m_vecPos;
}

Vector CTextComponent::GetOffset()
{
	return m_vecOffset;
}

void CTextComponent::Init()
{
}

void CTextComponent::Update()
{
}

void CTextComponent::PhysicsUpdate()
{
	m_vecPos = GetOwner()->GetPos() + m_vecOffset;
}

void CTextComponent::Render()
{
	RENDER->Text(m_vecPos.x, m_vecPos.y, m_strText);
}

void CTextComponent::Release()
{
}
