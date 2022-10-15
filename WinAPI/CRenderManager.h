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

	HDC m_hdc;			// ����Ʈ����(��� ����ȭ��)�� �׸� dc
	HDC m_hMemDC;		// �����(�׸����� ����ȭ��)�� �׸� dc
	HBITMAP m_hBMP;		// ����ۿ� ��Ʈ��(�̹���)

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
	void Rect(float startX, float startY, float endX, float endY);	// �簢�� �׸���
	void Circle(float x, float y, float radius);					// �� �׸���
	void Text(float x, float y, wstring str);						// �ؽ�Ʈ �׸���

	void SetPen(PenType type, COLORREF color = RGB(0, 0, 0), int width = 1);	// �� ����
	void SetBrush(BrushType type, COLORREF color = RGB(255, 255, 255));			// �귯�� ����
	void SetText(TextType type);
};

#define	RENDER	CRenderManager::GetInstance()