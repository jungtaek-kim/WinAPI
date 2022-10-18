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
	list<CGameObject*> m_listDeleteObject;		// DeleteObject �̺�Ʈ ����

	void Init();
	void Update();
	void Release();

public:
	void EventAddObject(CGameObject* pObj);		// ���������ӿ� �߰��� ������Ʈ �̺�Ʈ �߰�
	void EventDeleteObject(CGameObject* pObj);	// ���� ������ ������Ʈ �̺�Ʈ �߰�

private:
	void ProgressAddObject();					// ������ �ʱ⿡ �߰��� ������Ʈ�� �߰�
	void ProgressDeleteObject();				// ���� ������ ������Ʈ�� ǥ��, ���� ������ ǥ�õ� ������Ʈ�� ����
};

#define EVENT				CEventManager::GetInstance()
#define ADDOBJECT(pObj)		CEventManager::GetInstance()->EventAddObject(pObj)
#define DELETEOBJECT(pObj)	CEventManager::GetInstance()->EventDeleteObject(pObj)
