#pragma once
#include "CComponent.h"

enum class PenType;
enum class BrushType;

class CRectComponent : public CComponent
{
public:
	CRectComponent();
	virtual ~CRectComponent();

private:
	Vector m_vecPos;
	Vector m_vecOffset;
	Vector m_vecScale;

	PenType		m_penType;
	int			m_penWidth;
	COLORREF	m_penColor;

	BrushType	m_brushType;
	COLORREF	m_brushColor;

public:
	void SetOffset(Vector offset);
	void SetScale(Vector scale);

	void SetPenType(PenType type);
	void SetPenColor(COLORREF color);
	void SetPenWidth(int width);

	void SetBrushType(BrushType type);
	void SetBrushColor(COLORREF color);

public:
	Vector GetPos();
	Vector GetOffset();
	Vector GetScale();

	PenType GetPenType();
	COLORREF GetPenColor();
	int GetPenWidth();

	BrushType GetBrushType();
	COLORREF GetBrushColor();

private:
	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;
	void Render() override;
	void Release() override;
};

