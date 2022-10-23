#pragma once

class CCore;

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

private:
	void Init();
	void BeginDraw();
	void EndDraw();
	void Release();

public:
	
};

#define	RENDER	CRenderManager::GetInstance()