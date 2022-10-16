#include "framework.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
}

CGameObject::~CGameObject()
{
}

Vector CGameObject::GetPos()
{
	return m_vecPos;
}

void CGameObject::SetPos(Vector pos)
{
	m_vecPos = pos;
}

void CGameObject::SetPos(float x, float y)
{
	m_vecPos.x = x;
	m_vecPos.y = y;
}

Vector CGameObject::GetScale()
{
	return m_vecScale;
}

void CGameObject::SetScale(Vector scale)
{
	m_vecScale = scale;
}

void CGameObject::SetScale(float x, float y)
{
	m_vecScale.x = x;
	m_vecScale.y = y;
}
