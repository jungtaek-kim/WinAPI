#include "framework.h"
#include "CRenderManager.h"

#include "WinAPI.h"

CRenderManager::CRenderManager()
{
	m_hdc = 0;
	m_hMemDC = 0;
	m_hBMP = 0;

	hCurPen = 0;
	penType = PenType::Solid;
	penWidth = 1;
	penColor = RGB(0, 0, 0);

	hCurBrush = 0;
	brushType = BrushType::Solid;
	brushColor = RGB(255, 255, 255);

	textType = TextType::Top;
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

	// �⺻ �� & �귯�� ����
	SetPen(PenType::Solid);
	SetBrush(BrushType::Solid);
	SetText(TextType::Top);
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

	// ����ߴ� �� & �귯�� ����
	DeleteObject(hCurPen);
	DeleteObject(hCurBrush);
}

void CRenderManager::Pixel(float x, float y, COLORREF color)
{
	SetPixel(m_hMemDC, (int)x, (int)y, color);
}

void CRenderManager::Line(float startX, float startY, float endX, float endY)
{
	// WinGDI ����
	// 1. ������� ����귯�ø� ����
	// 2. �׸��� �۾� ����
	// 3. ������� �����귯�÷� ����
	// Why? �ٸ� �������� ����ϴ� ��� ������ ��츦 ���

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	MoveToEx(m_hMemDC, (int)startX, (int)startY, NULL);
	LineTo(m_hMemDC, (int)endX, (int)endY);

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY)
{
	// WinGDI ����
	// 1. ������� ����귯�ø� ����
	// 2. �׸��� �۾� ����
	// 3. ������� �����귯�÷� ����
	// Why? �ٸ� �������� ����ϴ� ��� ������ ��츦 ���

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	Rectangle(m_hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Circle(float x, float y, float radius)
{
	// WinGDI ����
	// 1. ������� ����귯�ø� ����
	// 2. �׸��� �۾� ����
	// 3. ������� �����귯�÷� ����
	// Why? �ٸ� �������� ����ϴ� ��� ������ ��츦 ���

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	Ellipse(m_hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Text(float x, float y, wstring str)
{
	// WinGDI ����
	// 1. ������� ����귯�ø� ����
	// 2. �׸��� �۾� ����
	// 3. ������� �����귯�÷� ����
	// Why? �ٸ� �������� ����ϴ� ��� ������ ��츦 ���

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	TextOut(m_hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::SetPen(PenType type, COLORREF color, int width)
{
	// �����ϴ� ���� ���� ��� ������ ��� ���� ������ ����
	if (penType == type && penWidth == width && penColor == color)
		return;

	// ���� ���� ����
	DeleteObject(hCurPen);

	// �� Ÿ�Կ� ���� �� ��Ÿ���� �ٸ��� ����
	switch (type)
	{
	case PenType::Solid:
		hCurPen = CreatePen(PS_SOLID, width, color);
		break;
	case PenType::Dot:
		hCurPen = CreatePen(PS_DOT, width, color);
		break;
	case PenType::Dash:
		hCurPen = CreatePen(PS_DASH, width, color);
		break;
	case PenType::Null:
		hCurPen = CreatePen(PS_NULL, width, color);
		break;
	default:
		hCurPen = CreatePen(PS_SOLID, width, color);
		break;
	}
}

void CRenderManager::SetBrush(BrushType type, COLORREF color)
{
	// �����ϴ� �귯�ð� ���� �귯�ÿ� ������ ��� ���� ������ ����
	if (brushType == type && brushColor == color)
		return;

	// ���� �귯�ø� ����
	DeleteObject(hCurBrush);

	// �귯�� Ÿ�Կ� ���� �귯�� ��Ÿ���� �ٸ��� ����
	switch (type)
	{
	case BrushType::Solid:
		hCurBrush = CreateSolidBrush(color);
		break;
	case BrushType::Null:
		// Null �귯�ø� ���� ����� ����
		// ��ǻ�ʹ� ����ǥ���� �Ұ��� -> Ư��ó�� �ʿ�
		hCurBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		break;
	default:
		hCurBrush = CreateSolidBrush(color);
		break;
	}
}

void CRenderManager::SetText(TextType type)
{
	if (textType == type)
		return;

	switch (type)
	{
	case TextType::Top:
		SetTextAlign(m_hMemDC, TA_TOP);
		break;
	case TextType::Bottom:
		SetTextAlign(m_hMemDC, TA_BOTTOM);
		break;
	case TextType::Left:
		SetTextAlign(m_hMemDC, TA_LEFT);
		break;
	case TextType::Right:
		SetTextAlign(m_hMemDC, TA_RIGHT);
		break;
	case TextType::Center:
		SetTextAlign(m_hMemDC, TA_CENTER);
		break;
	default:
		SetTextAlign(m_hMemDC, TA_TOP);
		break;
	}
}
