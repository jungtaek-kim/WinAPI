#include "framework.h"
#include "CAnimation.h"

CAnimation::CAnimation()
{
}

CAnimation::~CAnimation()
{
}

const wstring& CAnimation::GetName()
{
	return L"";
}

void CAnimation::SetName(const wstring& name)
{
}

void CAnimation::Create(CImage* pImg, Vector lt, Vector slice, Vector step, float duration, UINT count, bool repeat)
{
}

void CAnimation::Replay()
{
}

void CAnimation::Init()
{
}

void CAnimation::Update()
{
}

void CAnimation::Render()
{
}

void CAnimation::Release()
{
}
