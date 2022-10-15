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

	// 기본 펜 & 브러시 설정
	SetPen(PenType::Solid);
	SetBrush(BrushType::Solid);
	SetText(TextType::Top);
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

	// 사용했던 펜 & 브러시 삭제
	DeleteObject(hCurPen);
	DeleteObject(hCurBrush);
}

void CRenderManager::Pixel(float x, float y, COLORREF color)
{
	SetPixel(m_hMemDC, (int)x, (int)y, color);
}

void CRenderManager::Line(float startX, float startY, float endX, float endY)
{
	// WinGDI 사용법
	// 1. 현재펜과 현재브러시를 선택
	// 2. 그리기 작업 진행
	// 3. 이전펜과 이전브러시로 복구
	// Why? 다른 영역에서 사용하다 잠시 빌려쓴 경우를 대비

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	MoveToEx(m_hMemDC, (int)startX, (int)startY, NULL);
	LineTo(m_hMemDC, (int)endX, (int)endY);

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY)
{
	// WinGDI 사용법
	// 1. 현재펜과 현재브러시를 선택
	// 2. 그리기 작업 진행
	// 3. 이전펜과 이전브러시로 복구
	// Why? 다른 영역에서 사용하다 잠시 빌려쓴 경우를 대비

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	Rectangle(m_hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Circle(float x, float y, float radius)
{
	// WinGDI 사용법
	// 1. 현재펜과 현재브러시를 선택
	// 2. 그리기 작업 진행
	// 3. 이전펜과 이전브러시로 복구
	// Why? 다른 영역에서 사용하다 잠시 빌려쓴 경우를 대비

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	Ellipse(m_hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::Text(float x, float y, wstring str)
{
	// WinGDI 사용법
	// 1. 현재펜과 현재브러시를 선택
	// 2. 그리기 작업 진행
	// 3. 이전펜과 이전브러시로 복구
	// Why? 다른 영역에서 사용하다 잠시 빌려쓴 경우를 대비

	HPEN prevPen = static_cast<HPEN>(SelectObject(m_hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(m_hMemDC, hCurBrush));

	TextOut(m_hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());

	SelectObject(m_hMemDC, prevPen);
	SelectObject(m_hMemDC, prevBrush);
}

void CRenderManager::SetPen(PenType type, COLORREF color, int width)
{
	// 선택하는 펜이 현재 펜과 동일할 경우 새로 만들지 않음
	if (penType == type && penWidth == width && penColor == color)
		return;

	// 이전 펜을 제거
	DeleteObject(hCurPen);

	// 펜 타입에 따라 펜 스타일을 다르게 설정
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
	// 선택하는 브러시가 현재 브러시와 동일할 경우 새로 만들지 않음
	if (brushType == type && brushColor == color)
		return;

	// 이전 브러시를 제거
	DeleteObject(hCurBrush);

	// 브러시 타입에 따라 브러시 스타일을 다르게 설정
	switch (type)
	{
	case BrushType::Solid:
		hCurBrush = CreateSolidBrush(color);
		break;
	case BrushType::Null:
		// Null 브러시만 유독 희안한 구현
		// 컴퓨터는 투명표현이 불가능 -> 특별처리 필요
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
