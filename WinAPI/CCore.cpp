#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"

CCore::CCore()
{
	m_pointX = 100;
	m_pointY = 100;
}

CCore::~CCore()
{

}

void CCore::Init()
{
	TIME->Init();
	RENDER->Init();
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
	RENDER->BeginDraw();

	//// 게임 표현 내용
	RENDER->Rect(m_pointX - 50, m_pointY - 50, m_pointX + 50, m_pointY + 50);
	RENDER->Circle(200, 200, 100);
	RENDER->Line(300, 300, 400, 400);
	for (float i = 50; i < 80; i++)
	{
		for (float j = 50; j < 80; j++)
		{
			RENDER->Pixel(i, j, RGB(255, 0, 255));
		}
	}

	//// 우상단에 현재 게임FPS 출력 (60프레임 이상을 목표로 최적화 해야함)
	wstring frame = to_wstring(FPS);
	RENDER->Text(WINSIZEX - 50, 10, frame);

	RENDER->EndDraw();
}

void CCore::Release()
{
	TIME->Release();
	RENDER->Release();
}
