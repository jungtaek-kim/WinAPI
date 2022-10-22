#pragma once
#include "CComponent.h"

enum class TextType;

class CTextComponent : public CComponent
{
public:
	CTextComponent();
	virtual ~CTextComponent();

private:
	TextType m_type;
	wstring m_strText;
	Vector m_vecPos;
	Vector m_vecOffset;

public:
	void SetType(TextType type);
	void SetText(wstring text);
	void SetOffset(Vector offset);

public:
	TextType GetType();
	const wstring& GetText();
	Vector GetPos();
	Vector GetOffset();

private:
	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;
	void Render() override;
	void Release() override;
};

