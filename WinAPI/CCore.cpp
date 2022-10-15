#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

CCore::CCore()
{
	m_hdc = 0;
	m_point = { 200, 200 };
}

CCore::~CCore()
{

}

void CCore::Init()
{
	m_hdc = GetDC(hWnd);
}

void CCore::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_point.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_point.x += 1;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_point.y -= 1;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_point.y += 1;
	}
}

void CCore::Render()
{
	Rectangle(
		m_hdc,
		m_point.x - 50,
		m_point.y - 50,
		m_point.x + 50,
		m_point.y + 50
	);
}

void CCore::Release()
{
	ReleaseDC(hWnd, m_hdc);
}
