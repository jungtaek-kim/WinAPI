#pragma once

class CCore;

class CGameManager : public SingleTon<CGameManager>
{
	friend SingleTon<CGameManager>;
	friend CCore;
private:
	CGameManager();
	virtual ~CGameManager();

private:
	float m_fHighScore;
	float m_fCurScore;

public:
	void SetScore(float score);

	float GetScore();
	float GetHighScore();
};

#define GAME	CGameManager::GetInstance()