#include "framework.h"
#include "CImageComponent.h"

#include "CPathManager.h"
#include "CRenderManager.h"
#include "CResourceManager.h"
#include "CGameObject.h"
#include "CImage.h"

CImageComponent::CImageComponent()
{
	m_pImg = nullptr;
	m_type = ImageType::Bit;
	m_vecScale = Vector(100, 100);
	m_vecOffset = Vector(0, 0);
}

CImageComponent::~CImageComponent()
{
}

void CImageComponent::SetImage(CImage* pImg)
{
	m_pImg = pImg;
}

void CImageComponent::SetType(ImageType type)
{
	m_type = type;
}

void CImageComponent::SetOffset(Vector offset)
{
	m_vecOffset = offset;
}

void CImageComponent::SetScale(Vector scale)
{
	m_vecScale = scale;
}

CImage* CImageComponent::GetImage()
{
	return m_pImg;
}

ImageType CImageComponent::GetType()
{
	return m_type;
}

Vector CImageComponent::GetPos()
{
	return m_vecPos;
}

Vector CImageComponent::GetOffset()
{
	return m_vecOffset;
}

Vector CImageComponent::GetScale()
{
	return m_vecScale;
}

void CImageComponent::Init()
{
}

void CImageComponent::Update()
{
}

void CImageComponent::PhysicsUpdate()
{
	m_vecPos = GetOwner()->GetPos() + m_vecOffset;
}

void CImageComponent::Render()
{
	if (m_type == ImageType::Bit)
		RENDER->BitImage(m_pImg,
			m_vecPos.x - m_vecScale.x * 0.5f,
			m_vecPos.y - m_vecScale.y * 0.5f,
			m_vecPos.x + m_vecScale.x * 0.5f,
			m_vecPos.y + m_vecScale.y * 0.5f);
	else if (m_type == ImageType::Stretch)
		RENDER->StrectchImage(m_pImg,
			m_vecPos.x - m_vecScale.x * 0.5f,
			m_vecPos.y - m_vecScale.y * 0.5f,
			m_vecPos.x + m_vecScale.x * 0.5f,
			m_vecPos.y + m_vecScale.y * 0.5f);
	else if (m_type == ImageType::Transparent)
		RENDER->TransparentImage(m_pImg,
			m_vecPos.x - m_vecScale.x * 0.5f,
			m_vecPos.y - m_vecScale.y * 0.5f,
			m_vecPos.x + m_vecScale.x * 0.5f,
			m_vecPos.y + m_vecScale.y * 0.5f);
}

void CImageComponent::Release()
{
}
