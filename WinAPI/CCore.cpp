#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"

CCore::CCore()
{
	m_hdc = 0;
	m_pointX = 100;
	m_pointY = 100;
}

CCore::~CCore()
{

}

void CCore::Init()
{
	TIME->Init();

	m_hdc = GetDC(hWnd);
}

void CCore::Update()
{
	TIME->Update();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pointX -= 100 * DT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pointX += 100 * DT;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pointY -= 100 * DT;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pointY += 100 * DT;
	}
}

void CCore::Render()
{
	Rectangle(
		m_hdc,
		m_pointX - 50,
		m_pointY - 50,
		m_pointX + 50,
		m_pointY + 50
	);
}

void CCore::Release()
{
	TIME->Release();

	ReleaseDC(hWnd, m_hdc);
}
