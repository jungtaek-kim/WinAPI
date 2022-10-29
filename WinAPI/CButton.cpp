#include "framework.h"
#include "CButton.h"

#include "CRenderManager.h"

CButton::CButton()
{
	m_pCallback = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
}

CButton::~CButton()
{
}

void CButton::SetClickedCallback(CallbackFunc pCallback, DWORD_PTR pParam1, DWORD_PTR pParam2)
{
	m_pCallback = pCallback;
	m_pParam1 = pParam1;
	m_pParam2 = pParam2;
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
		Color(255, 255, 255, 1)
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
}

void CButton::OnMouseExit()
{
	Logger::Debug(m_strName + L" button exit");
}

void CButton::OnMouseUp()
{
	Logger::Debug(m_strName + L" button up");
}

void CButton::OnMouseDown()
{
	if (nullptr != m_pCallback)
		m_pCallback(m_pParam1, m_pParam2);
	Logger::Debug(m_strName + L" button down");
}

void CButton::OnMouseClicked()
{
	Logger::Debug(m_strName + L" button click");
}
