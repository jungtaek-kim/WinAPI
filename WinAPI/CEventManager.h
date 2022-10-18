#pragma once

class CCore;

class CEventManager : public SingleTon<CEventManager>
{
	friend SingleTon<CEventManager>;
	friend CCore;
private:
	CEventManager();
	virtual ~CEventManager();

	void Init();
	void Update();
	void Release();
};

#define EVENT	CEventManager::GetInstance()
