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
	ID2D1Factory*			m_pFactory;			// D2D ���丮
	ID2D1HwndRenderTarget*	m_pRenderTarget;	// �׷��� �ϴ� ȭ�� (D2D�� HDC)
	IWICImagingFactory*		m_pImageFactory;	// �̹��� ���丮
	IDWriteFactory*			m_pWriteFactory;	// �׸��� ���丮

	ID2D1SolidColorBrush*	m_pDefaultBrush;		// ������ �׸��� ���� �귯��
	IDWriteTextFormat*		m_pDefaultTextFormat;	// �ؽ�Ʈ�� �׸��� ���� ����

private:
	void Init();
	void BeginDraw();
	void EndDraw();
	void Release();

public:
	
};

#define	RENDER	CRenderManager::GetInstance()