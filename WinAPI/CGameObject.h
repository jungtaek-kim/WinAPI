#pragma once

class CScene;

// 게임오브젝트 : 
// 씬 내에 존재하는 물체, ex) 캐릭터, 미사일, 몬스터, 아이템, 등
// 게임오브젝트를 캡슐화하여 행동과 표현을 정의할 경우
// 다른 게임오브젝트와 독립적으로 설계할 수 있음
class CGameObject
{
	friend CScene;
protected:
	Vector m_vecPos;	// 게임오브젝트의 위치
	Vector m_vecScale;	// 게임오브젝트의 크기

public:
	CGameObject();
	virtual ~CGameObject();

	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);

private:
	virtual void Init() = 0;		// 초기화
	virtual void Update() = 0;		// 게임오브젝트의 행동정의
	virtual void Render() = 0;		// 게임오브젝트의 표현정의
	virtual void Release() = 0;		// 마무리
};
