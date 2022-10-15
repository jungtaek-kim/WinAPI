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
	// 전체를 다시 흰색으로 그려 잔상을 삭제
	Rectangle(m_hdc, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// 게임 표현 내용
	Rectangle(
		m_hdc,
		m_pointX - 50,
		m_pointY - 50,
		m_pointX + 50,
		m_pointY + 50
	);

	// 우상단에 현재 게임FPS 출력 (60프레임 이상을 목표로 최적화 해야함)
	wstring frame = to_wstring(FPS);
	TextOutW(m_hdc, WINSIZEX - 50, 10, frame.c_str(), frame.size());
}

void CCore::Release()
{
	TIME->Release();

	ReleaseDC(hWnd, m_hdc);
}
