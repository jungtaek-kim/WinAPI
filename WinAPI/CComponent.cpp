#include "framework.h"
#include "CComponent.h"

CComponent::CComponent()
{
	m_pOwner = nullptr;
	m_iZOrder = 0;
}

CComponent::~CComponent()
{
}

void CComponent::SetOwner(CGameObject* pOwner)
{
	m_pOwner = pOwner;
}

void CComponent::SetZOrder(int zOrder)
{
	m_iZOrder = zOrder;
}

CGameObject* CComponent::GetOwner()
{
	return m_pOwner;
}

int CComponent::GetZOrder()
{
	return m_iZOrder;
}
