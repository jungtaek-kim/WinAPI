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
	ID2D1Factory*			m_pFactory;			// D2D ���丮
	ID2D1HwndRenderTarget*	m_pRenderTarget;	// �׷��� �ϴ� ȭ�� (D2D�� HDC)
	IWICImagingFactory*		m_pImageFactory;	// �̹��� ���丮
	IDWriteFactory*			m_pWriteFactory;	// �׸��� ���丮

	ID2D1SolidColorBrush*	m_pDefaultBrush;		// ������ �׸��� ���� �귯��
	IDWriteTextFormat*		m_pDefaultTextFormat;	// �ؽ�Ʈ�� �׸��� ���� ����

	ID2D1SolidColorBrush*	m_pCurBrush;		// ���� �귯��
	IDWriteTextFormat*		m_pCurTextFormat;	// ���� �ؽ�Ʈ ����

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