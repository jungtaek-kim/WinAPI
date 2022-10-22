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
	CImage* m_pImg;			// 이미지
	ImageType m_type;		// 이미지의 타입
	Vector m_vecPos;		// 이미지의 위치
	Vector m_vecOffset;		// 이미지의 변위차(수정값)
	Vector m_vecScale;		// 이미지의 크기

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

