#include "framework.h"
#include "CRenderManager.h"

#include "WinAPI.h"
#include "CImage.h"

CRenderManager::CRenderManager()
{
	m_pFactory		= nullptr;
	m_pRenderTarget	= nullptr;
	m_pImageFactory = nullptr;
	m_pWriteFactory = nullptr;

	m_pDefaultBrush		= nullptr;
	m_pDefaultTextFormat	= nullptr;
}

CRenderManager::~CRenderManager()
{

}

void CRenderManager::Init()
{
	HRESULT hResult;

	// D2D1Factory ����
	hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	assert(S_OK == hResult && "D2D1Factory Create Failed");

	// ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸��� ���� Render Target�� ����
	hResult = m_pFactory->CreateHwndRenderTarget
	(
		RenderTargetProperties(),
		HwndRenderTargetProperties(
			hWnd,
			SizeU(WINSIZEX, WINSIZEY),
			D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_pRenderTarget
	);
	assert(S_OK == hResult && "HwndRenderTarget Create Failed");

	// WICImagingFactory ����
	hResult = CoInitialize(nullptr);
	assert(S_OK == hResult && "CoInitialize Failed");

	hResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));
	assert(S_OK == hResult && "ImageFactory Create Failed");

	hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory));
	assert(S_OK == hResult && "WriteFactory Create Failed");

	// �ؽ�Ʈ ���� ����
	hResult = m_pWriteFactory->CreateTextFormat(
		L"����",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		10.f,
		L"ko",
		&m_pDefaultTextFormat);
	assert(S_OK == hResult && "TextFormat Create Failed");

	hResult = m_pDefaultTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	assert(S_OK == hResult && "TextFormat SetAlignment Failed");

	hResult = m_pDefaultTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	assert(S_OK == hResult && "TextFormat SetParagraphAlignment Failed");

	// �귯�� ����
	hResult = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.f, 0.f, 0.f), &m_pDefaultBrush);
	assert(S_OK == hResult && "SolidColorBrush Create Failed");
}

void CRenderManager::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
}

void CRenderManager::EndDraw()
{
	m_pRenderTarget->EndDraw();
}

void CRenderManager::Release()
{
	// �������� �ʱ�ȭ�� ��������

	if (nullptr != m_pDefaultBrush)
	{
		m_pDefaultBrush->Release();
		m_pDefaultBrush = nullptr;
	}
	if (nullptr != m_pDefaultTextFormat)
	{
		m_pDefaultTextFormat->Release();
		m_pDefaultTextFormat = nullptr;
	}
	if (nullptr != m_pWriteFactory)
	{
		m_pWriteFactory->Release();
		m_pWriteFactory = nullptr;
	}
	if (nullptr != m_pImageFactory)
	{
		m_pImageFactory->Release();
		m_pImageFactory = nullptr;
	}
	if (nullptr != m_pRenderTarget)
	{
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}
	if (nullptr != m_pFactory)
	{
		m_pFactory->Release();
		m_pFactory = nullptr;
	}
}