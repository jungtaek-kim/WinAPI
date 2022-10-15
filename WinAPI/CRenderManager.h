#pragma once

class CCore;

class CRenderManager : public SingleTon<CRenderManager>
{
	friend SingleTon<CRenderManager>;
	friend CCore;
private:
	CRenderManager();
	virtual ~CRenderManager();

	HDC m_hdc;			// ����Ʈ����(��� ����ȭ��)�� �׸� dc
	HDC m_hMemDC;		// �����(�׸����� ����ȭ��)�� �׸� dc
	HBITMAP m_hBMP;		// ����ۿ� ��Ʈ��(�̹���)

	void Init();
	void BeginDraw();
	void EndDraw();
	void Release();

public:
	void Pixel(float x, float y, COLORREF color);
	void Line(float startX, float startY, float endX, float endY);
	void Rect(float startX, float startY, float endX, float endY);	// �簢�� �׸���
	void Circle(float x, float y, float radius);					// �� �׸���
	void Text(float x, float y, wstring str);						// �ؽ�Ʈ �׸���
};

#define	RENDER	CRenderManager::GetInstance()