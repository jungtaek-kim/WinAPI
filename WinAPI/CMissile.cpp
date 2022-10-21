#include "framework.h"
#include "CMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"

CMissile::CMissile()
{
	m_vecScale = Vector(10, 10);
	m_layer = Layer::Missile;
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
	AddCollider(Vector(10, 10), Vector(0, 0));
}

void CMissile::Update()
{
	m_vecPos.x += 300 * DT;

	// 임시로 삭제 구현
	if (m_vecPos.x > 1000)
		DELETEOBJECT(this);
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