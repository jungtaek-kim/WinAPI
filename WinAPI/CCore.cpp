#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"

CCore::CCore()
{
	m_pointX = 100;
	m_pointY = 100;
	m_pointMouseX = 0;
	m_pointMouseY = 0;
}

CCore::~CCore()
{

}

void CCore::Init()
{
	TIME->Init();
	RENDER->Init();
	INPUT->Init();
}

void CCore::Update()
{
	TIME->Update();
	INPUT->Update();

	if (BUTTONSTAY(VK_LEFT))
	{
		m_pointX -= 100 * DT;
	}

	if (BUTTONSTAY(VK_RIGHT))
	{
		m_pointX += 100 * DT;
	}

	if (BUTTONSTAY(VK_UP))
	{
		m_pointY -= 100 * DT;
	}

	if (BUTTONSTAY(VK_DOWN))
	{
		m_pointY += 100 * DT;
	}

	m_pointMouseX = (float)MOUSEPOS.x;
	m_pointMouseY = (float)MOUSEPOS.y;
}

void CCore::Render()
{
	RENDER->BeginDraw();

	//// 게임 표현 내용
	RENDER->SetPen(PenType::Dot, RGB(255, 0, 0));
	RENDER->SetBrush(BrushType::Null);

	RENDER->Rect(m_pointX - 50, m_pointY - 50, m_pointX + 50, m_pointY + 50);
	RENDER->Circle(m_pointMouseX, m_pointMouseY, 50);

	//// 우상단에 현재 게임FPS 출력 (60프레임 이상을 목표로 최적화 해야함)
	wstring frame = to_wstring(FPS);
	RENDER->Text(WINSIZEX - 50, 10, frame);

	RENDER->EndDraw();
}

void CCore::Release()
{
	TIME->Release();
	RENDER->Release();
	INPUT->Release();
}
