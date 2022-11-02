#include "framework.h"
#include "CSound.h"

CSound::CSound()
{
	m_pSound = nullptr;
	m_pChannel = nullptr;
}

CSound::~CSound()
{
	if (nullptr != m_pSound)
	{
		m_pSound->release();
	}
}

bool CSound::IsPlaying()
{
	return false;
}

bool CSound::IsPaused()
{
	return false;
}

void CSound::Load(const wstring& soundName)
{
}
