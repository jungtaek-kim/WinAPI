#include "framework.h"
#include "CAnimator.h"

CAnimator::CAnimator()
{
}

CAnimator::~CAnimator()
{
}

void CAnimator::Init()
{
}

void CAnimator::Update()
{
}

void CAnimator::Render()
{
}

void CAnimator::Release()
{
}

void CAnimator::CreateAnimation(const wstring& aniName, CImage* pImg, Vector lt, Vector slice, Vector step, float duration, UINT count, bool repeat)
{
}

void CAnimator::RemoveAnimation(const wstring& aniName)
{
}

CAnimation* CAnimator::FindAnimation(const wstring& aniName)
{
	return nullptr;
}

void CAnimator::Play(const wstring& aniName, bool trigger)
{
}

void CAnimator::Stop()
{
}
