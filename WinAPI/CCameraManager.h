#pragma once

class CCore;
class CGameObject;

class CCameraManager : public SingleTon<CCameraManager>
{
	friend SingleTon<CCameraManager>;
	friend CCore;
private:
	CCameraManager();
	virtual ~CCameraManager();

private:
	Vector			m_vecLookAt;	// 카메라가 현재 보고있는 위치
	Vector			m_vecTargetPos;	// 카메라의 목표 위치
	CGameObject*	m_pTargetObj;	// 카메라가 추적할 오브젝트

public:
	Vector			GetLookAt();
	Vector			GetTargetPos();
	CGameObject*	GetTargetObj();

	// 오브젝트를 지정할 경우 목표위치는 목표 오브젝트의 위치로 지정됨
	void SetTargetPos(Vector targetPos);		// 카메라의 목표 위치 지정
	void SetTargetObj(CGameObject* pTargetObj);	// 카메라의 목표 오브젝트 지정

	Vector WorldToScreenPoint(Vector worldPoint);	// 게임위치->화면위치
	Vector ScreenToWorldPoint(Vector screenPoint);	// 화면위치->게임위치

private:
	void Init();
	void Update();
	void Release();

private:
	void MoveToTarget();
};

#define CAMERA	CCameraManager::GetInstance()