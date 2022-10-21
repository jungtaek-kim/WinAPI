#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"

CMonster::CMonster()
{
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	AddCollider(Vector(90, 90), Vector(0, 0));
}

void CMonster::Update()
{
}

void CMonster::Render()
{
	RENDER->Rect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);
}

void CMonster::Release()
{
}
