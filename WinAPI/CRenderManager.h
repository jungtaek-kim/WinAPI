#pragma once

class CCore;

enum class PenType { Solid, Dot, Dash, Null };
enum class BrushType { Solid, Null };
enum class TextType { Top, Bottom, Left, Right, Center };

class CRenderManager : public SingleTon<CRenderManager>
{
	friend SingleTon<CRenderManager>;
	friend CCore;
private:
	CRenderManager();
	virtual ~CRenderManager();

	HDC m_hdc;			// 프론트버퍼(결과 게임화면)에 그릴 dc
	HDC m_hMemDC;		// 백버퍼(그리는중 게임화면)에 그릴 dc
	HBITMAP m_hBMP;		// 백버퍼용 비트맵(이미지)

	HPEN		hCurPen;
	PenType		penType;
	int			penWidth;
	COLORREF	penColor;

	HBRUSH		hCurBrush;
	BrushType	brushType;
	COLORREF	brushColor;

	TextType	textType;

	void Init();
	void BeginDraw();
	void EndDraw();
	void Release();

public:
	void Pixel(float x, float y, COLORREF color);
	void Line(float startX, float startY, float endX, float endY);
	void Rect(float startX, float startY, float endX, float endY);	// 사각형 그리기
	void Circle(float x, float y, float radius);					// 원 그리기
	void Text(float x, float y, wstring str);						// 텍스트 그리기

	void SetPen(PenType type, COLORREF color = RGB(0, 0, 0), int width = 1);	// 펜 설정
	void SetBrush(BrushType type, COLORREF color = RGB(255, 255, 255));			// 브러시 설정
	void SetText(TextType type);
};

#define	RENDER	CRenderManager::GetInstance()