#include "framework.h"
#include "CMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"

CMissile::CMissile()
{
	m_vecScale = Vector(10, 10);
	m_layer = Layer::Missile;
	m_strName = L"미사일";
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0));
}

void CMissile::Update()
{
	m_vecPos.x += 300 * DT;

	// 화면밖으로 나갈경우 삭제
	if (m_vecPos.x > WINSIZEX)
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

void CMissile::OnCollisionEnter(CCollider* pOtherCollider)
{
	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");
	DELETEOBJECT(this);
}
