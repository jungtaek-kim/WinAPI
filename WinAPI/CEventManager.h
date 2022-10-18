#pragma once

class CCore;
class CGameObject;

class CEventManager : public SingleTon<CEventManager>
{
	friend SingleTon<CEventManager>;
	friend CCore;
private:
	CEventManager();
	virtual ~CEventManager();

	list<CGameObject*> m_listAddObject;			// AddObject 이벤트 보관

	void Init();
	void Update();
	void Release();

public:
	void EventAddObject(CGameObject* pObj);		// 다음프레임에 추가될 오브젝트 이벤트 추가

private:
	void ProgressAddObject();					// 프레임 초기에 추가될 오브젝트를 추가
};

#define EVENT				CEventManager::GetInstance()
#define ADDOBJECT(pObj)		CEventManager::GetInstance()->EventAddObject(pObj)
