#pragma once

class CEventManager;
class CScene;
class CComponent;

// 게임오브젝트 : 
// 씬 내에 존재하는 물체, ex) 캐릭터, 미사일, 몬스터, 아이템, 등
// 게임오브젝트를 캡슐화하여 행동과 표현을 정의할 경우
// 다른 게임오브젝트와 독립적으로 설계할 수 있음
class CGameObject
{
	friend CEventManager;
	friend CScene;
public:
	CGameObject();
	virtual ~CGameObject();

protected:
	Vector m_vecPos;	// 게임오브젝트의 위치
	Vector m_vecScale;	// 게임오브젝트의 크기

public:
	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);

private:
	bool m_bReservedDelete;		// 게임오브젝트가 삭제예정인지 여부
	bool m_bSafeToDelete;		// 게임오브젝트가 삭제해도 문제없는지 여부

	void SetReserveDelete();	// 게임오브젝트 삭제 예약
	bool GetSafeToDelete();		// 게임오브젝트 삭제 가능 상태 확인
	void SetSafeToDelete();		// 게임오브젝트 삭제 가능 상태 표시
public:
	bool GetReserveDelete();		// 게임오브젝트가 삭제예정인지 확인

private:
	list<CComponent*> m_listComponent;	// 컴포넌트들을 보관할 자료구조

	void AddComponent(CComponent* component);		// 컴포넌트 추가
	void RemoveComponent(CComponent* component);	// 컴포넌트 삭제

private:
	virtual void Init() = 0;		// 초기화
	virtual void Update() = 0;		// 게임오브젝트의 행동정의
	virtual void Render() = 0;		// 게임오브젝트의 표현정의
	virtual void Release() = 0;		// 마무리
};
