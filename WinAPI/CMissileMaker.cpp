#include "framework.h"
#include "CMissileMaker.h"

#include "CEventManager.h"
#include "CTimeManager.h"
#include "CMissile.h"

CMissileMaker::CMissileMaker()
{
	m_fLastShootTime = 0;
	m_fRepeatTime = 0.1f;
}

CMissileMaker::~CMissileMaker()
{
}

void CMissileMaker::Init()
{
	m_fRepeatTime = 0.1f;
}

void CMissileMaker::Update()
{
	m_fLastShootTime += DT;
	if (m_fLastShootTime > m_fRepeatTime)
	{
		m_fLastShootTime = 0;
		CreateRandomMissile();
	}
}

void CMissileMaker::Render()
{
}

void CMissileMaker::Release()
{
}

float CMissileMaker::GetRepeatTime()
{
	return m_fRepeatTime;
}

void CMissileMaker::SetRepeatTime(float repeatTime)
{
	m_fRepeatTime = repeatTime;
}

void CMissileMaker::LevelUp()
{
	m_fRepeatTime *= 0.9f;
	if (m_fRepeatTime < 0.02f)
		m_fRepeatTime = 0.02f;
}

void CMissileMaker::CreateRandomMissile()
{
	int side = rand() % 4;
	if (side == 0)	// 위
	{
		int randPos = rand() % WINSIZEX;
		float randAngle = rand() % 100 - 50;
		CMissile* pMissile = new CMissile;
		pMissile->SetDir(Vector(randAngle, 10));
		pMissile->SetPos(Vector(randPos, 0));
		ADDOBJECT(pMissile);
	}
	else if (side == 1) // 아래
	{
		int randPos = rand() % WINSIZEX;
		float randAngle = rand() % 100 - 50;
		CMissile* pMissile = new CMissile;
		pMissile->SetDir(Vector(randAngle, -10));
		pMissile->SetPos(Vector(randPos, WINSIZEY));
		ADDOBJECT(pMissile);
	}
	else if (side == 2) // 왼쪽
	{
		int randPos = rand() % WINSIZEY;
		float randAngle = rand() % 100 - 50;
		CMissile* pMissile = new CMissile;
		pMissile->SetDir(Vector(10, randAngle));
		pMissile->SetPos(Vector(0, randPos));
		ADDOBJECT(pMissile);
	}
	else if (side == 3) // 오른쪽
	{
		int randPos = rand() % WINSIZEY;
		float randAngle = rand() % 10 - 5;
		CMissile* pMissile = new CMissile;
		pMissile->SetDir(Vector(-10, randAngle));
		pMissile->SetPos(Vector(WINSIZEX, randPos));
		ADDOBJECT(pMissile);
	}
}