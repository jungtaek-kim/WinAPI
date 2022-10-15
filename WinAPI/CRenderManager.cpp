#include "framework.h"
#include "CRenderManager.h"

#include "WinAPI.h"

CRenderManager::CRenderManager()
{
	m_hdc = 0;
	m_hMemDC = 0;
	m_hBMP = 0;
}

CRenderManager::~CRenderManager()
{

}

void CRenderManager::Init()
{
	m_hdc = GetDC(hWnd);

	// <더블 버퍼링>
	// 현재 게임화면에 직접 그릴경우 그리는 과정이 포착되어
	// 반짝거리는 블링크 현상 발생
	// 백버퍼에 그리는 작업을 진행하고 모두 그렸을 경우
	// 브론트버퍼에 결과물을 복사해주는 방식으로 블링크 현상을 해결

	// 더블 버퍼링의 메모리 DC와 비트맵 생성
	m_hMemDC = CreateCompatibleDC(m_hdc);
	m_hBMP = CreateCompatibleBitmap(m_hdc, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(m_hMemDC, m_hBMP));
	DeleteObject(hOldBitmap);
}

void CRenderManager::BeginDraw()
{
	// 백버퍼를 모두 흰색으로 초기화
	PatBlt(m_hMemDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
}

void CRenderManager::EndDraw()
{
	// 백버퍼를 프론트버퍼로 복사
	BitBlt(m_hdc, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CRenderManager::Release()
{
	// 사용했던 프론트버퍼와 백버퍼 삭제
	DeleteObject(m_hMemDC);
	DeleteObject(m_hBMP);
	ReleaseDC(hWnd, m_hdc);

	m_hdc = 0;
	m_hMemDC = 0;
	m_hBMP = 0;
}

void CRenderManager::Pixel(float x, float y, COLORREF color)
{
	SetPixel(m_hMemDC, (int)x, (int)y, color);
}

void CRenderManager::Line(float startX, float startY, float endX, float endY)
{
	MoveToEx(m_hMemDC, (int)startX, (int)startY, NULL);
	LineTo(m_hMemDC, (int)endX, (int)endY);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY)
{
	Rectangle(m_hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);
}

void CRenderManager::Circle(float x, float y, float radius)
{
	Ellipse(m_hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));
}

void CRenderManager::Text(float x, float y, wstring str)
{
	TextOut(m_hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());
}
