#pragma once
#include "CComponent.h"

class CImage;

enum class ImageType { Bit, Stretch, Transparent };

class CImageComponent : public CComponent
{
public:
	CImageComponent();
	virtual ~CImageComponent();

private:
	CImage* m_pImg;			// �̹���
	ImageType m_type;		// �̹����� Ÿ��
	Vector m_vecPos;		// �̹����� ��ġ
	Vector m_vecOffset;		// �̹����� ������(������)
	Vector m_vecScale;		// �̹����� ũ��

public:
	void SetImage(CImage* pImg);
	void SetType(ImageType type);
	void SetOffset(Vector offset);
	void SetScale(Vector scale);

public:
	CImage* GetImage();
	ImageType GetType();
	Vector GetPos();
	Vector GetOffset();
	Vector GetScale();

private:
	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;
	void Render() override;
	void Release() override;
};

