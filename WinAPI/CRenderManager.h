#pragma once

class CCore;

struct Color
{
	Color(BYTE r, BYTE g, BYTE b, FLOAT a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	BYTE r, g, b;
	FLOAT a;
};

class CRenderManager : public SingleTon<CRenderManager>
{
	friend SingleTon<CRenderManager>;
	friend CCore;
private:
	CRenderManager();
	virtual ~CRenderManager();

private:
	ID2D1Factory*			m_pFactory;			// D2D 팩토리
	ID2D1HwndRenderTarget*	m_pRenderTarget;	// 그려야 하는 화면 (D2D용 HDC)
	IWICImagingFactory*		m_pImageFactory;	// 이미지 팩토리
	IDWriteFactory*			m_pWriteFactory;	// 그리기 팩토리

	ID2D1SolidColorBrush*	m_pDefaultBrush;		// 도형을 그리기 위한 브러시
	IDWriteTextFormat*		m_pDefaultTextFormat;	// 텍스트를 그리기 위한 포멧

	ID2D1SolidColorBrush*	m_pCurBrush;		// 현재 브러시
	IDWriteTextFormat*		m_pCurTextFormat;	// 현재 텍스트 포멧

private:
	void Init();
	void BeginDraw();
	void EndDraw();
	void Release();

public:
	void SetBrush(Color color);
	void SetTextFormat(
		wstring fontName,
		DWRITE_FONT_WEIGHT fontWeight,
		DWRITE_FONT_STYLE fontStyle,
		DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize,
		wstring localeName = L"ko");
	void SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment);
	void SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);
};

#define	RENDER	CRenderManager::GetInstance()