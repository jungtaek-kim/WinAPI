#include "framework.h"
#include "CGameManager.h"

CGameManager::CGameManager()
{
	m_fCurScore = 0;
	m_fHighScore = 0;
}

CGameManager::~CGameManager()
{
}

void CGameManager::SetScore(float score)
{
	m_fCurScore = score;
	if (score > m_fHighScore)
		m_fHighScore = score;
}

float CGameManager::GetScore()
{
	return m_fCurScore;
}

float CGameManager::GetHighScore()
{
	return m_fHighScore;
}
