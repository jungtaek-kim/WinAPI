#pragma once
#pragma comment(lib, "Msimg32.lib")

class CCore;
class CImage;

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
	void Pixel(float x, float y, COLORREF color);						// �ȼ� �׸���
	void Line(float startX, float startY, float endX, float endY);		// �� �׸���
	void Rect(float startX, float startY, float endX, float endY);		// �簢�� �׸���
	void Circle(float x, float y, float radius);						// �� �׸���
	void Ellipse(float startX, float startY, float endX, float endY);	// Ÿ�� �׸���
	void Text(float x, float y, wstring str);							// �ؽ�Ʈ �׸���
	void BitImage(CImage* pImg, float startX, float startY, float endX, float endY);		// �̹��� �׸���
	void StrectchImage(CImage* pImg, float startX, float startY, float endX, float endY);	// ũ�⺯���̹��� �׸���
	void TransparentImage(CImage* pImg, float startX, float startY, float endX, float endY,	// �����̹��� �׸���
		COLORREF transparent = RGB(255, 0, 255));

	void SetPen(PenType type = PenType::Solid, COLORREF color = RGB(0, 0, 0), int width = 1);	// �� ����
	void SetBrush(BrushType type = BrushType::Solid, COLORREF color = RGB(255, 255, 255));			// �귯�� ����
	void SetText(TextType type);

	HDC GetMemDC();
};

#define	RENDER	CRenderManager::GetInstance()
#define GETDC	CRenderManager::GetInstance()->GetMemDC()