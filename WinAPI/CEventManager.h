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

	list<CGameObject*> m_listAddObject;			// AddObject �̺�Ʈ ����

	void Init();
	void Update();
	void Release();

public:
	void EventAddObject(CGameObject* pObj);		// ���������ӿ� �߰��� ������Ʈ �̺�Ʈ �߰�

private:
	void ProgressAddObject();					// ������ �ʱ⿡ �߰��� ������Ʈ�� �߰�
};

#define EVENT				CEventManager::GetInstance()
#define ADDOBJECT(pObj)		CEventManager::GetInstance()->EventAddObject(pObj)
