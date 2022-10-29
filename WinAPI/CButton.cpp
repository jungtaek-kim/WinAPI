#include "framework.h"
#include "CButton.h"

#include "CRenderManager.h"

CButton::CButton()
{
	m_colorRect = Color(255, 255, 255, 1);
}

CButton::~CButton()
{
}

void CButton::Init()
{
}

void CButton::Update()
{
}

void CButton::Render()
{
	RENDER->FillRect(
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		m_colorRect
	);

	RENDER->FrameRect(
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		Color(0, 0, 0, 1)
	);
}

void CButton::Release()
{
}

void CButton::OnMouseEnter()
{
	Logger::Debug(m_strName + L" button enter");
}

void CButton::OnMouseOver()
{
	m_colorRect = Color(0, 255, 0, 1);
}

void CButton::OnMouseExit()
{
	Logger::Debug(m_strName + L" button exit");
	m_colorRect = Color(255, 255, 255, 1);
}

void CButton::OnMouseUp()
{
	Logger::Debug(m_strName + L" button up");
}

void CButton::OnMouseDown()
{
	Logger::Debug(m_strName + L" button down");
}

void CButton::OnMouseClicked()
{
	Logger::Debug(m_strName + L" button click");
}
