#include "framework.h"
#include "CMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"

CMissile::CMissile()
{
	m_vecScale = Vector(10, 10);
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
}

void CMissile::Update()
{
	m_vecPos.x += 300 * DT;
}

void CMissile::Render()
{
	RENDER->Circle(
		m_vecPos.x,
		m_vecPos.y,
		m_vecScale.x);
}

void CMissile::Release()
{
}