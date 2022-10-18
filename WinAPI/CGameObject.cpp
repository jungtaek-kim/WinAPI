#include "framework.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
	m_bReservedDelete = false;
	m_bSafeToDelete = false;
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

bool CGameObject::GetReserveDelete()
{
    return m_bReservedDelete;
}

void CGameObject::SetReserveDelete()
{
	m_bReservedDelete = true;
}

bool CGameObject::GetSafeToDelete()
{
	return m_bSafeToDelete;
}

void CGameObject::SetSafeToDelete()
{
	m_bSafeToDelete = true;
}