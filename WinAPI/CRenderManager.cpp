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

	// <���� ���۸�>
	// ���� ����ȭ�鿡 ���� �׸���� �׸��� ������ �����Ǿ�
	// ��¦�Ÿ��� ��ũ ���� �߻�
	// ����ۿ� �׸��� �۾��� �����ϰ� ��� �׷��� ���
	// ���Ʈ���ۿ� ������� �������ִ� ������� ��ũ ������ �ذ�

	// ���� ���۸��� �޸� DC�� ��Ʈ�� ����
	m_hMemDC = CreateCompatibleDC(m_hdc);
	m_hBMP = CreateCompatibleBitmap(m_hdc, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(m_hMemDC, m_hBMP));
	DeleteObject(hOldBitmap);
}

void CRenderManager::BeginDraw()
{
	// ����۸� ��� ������� �ʱ�ȭ
	PatBlt(m_hMemDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
}

void CRenderManager::EndDraw()
{
	// ����۸� ����Ʈ���۷� ����
	BitBlt(m_hdc, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CRenderManager::Release()
{
	// ����ߴ� ����Ʈ���ۿ� ����� ����
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
