#pragma once

class CCore;

class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
	friend CCore;
private:
	CInputManager();
	virtual ~CInputManager();

	static const int VKEY_SIZE = 0xFF;	// VK의 최대 갯수

	bool m_arrPrevKey[VKEY_SIZE];		// 이전 키의 입력상태
	bool m_arrCurKey[VKEY_SIZE];		// 현재 키의 입력상태
	POINT m_ptMousePos;					// 현재 마우스 위치

	void Init();
	void Update();
	void Release();

public:

	bool GetButton(const int key);		// 키를 누르고 있는 중
	bool GetButtonUp(const int key);	// 키가 올라간 순간
	bool GetButtonDown(const int key);	// 키가 내려간 순간
	POINT GetMousePos();				// 현재 마우스 위치
};

#define	INPUT			CInputManager::GetInstance()
#define BUTTONSTAY(key)	CInputManager::GetInstance()->GetButton(key)
#define BUTTONUP(key)	CInputManager::GetInstance()->GetButtonUp(key)	
#define BUTTONDOWN(key)	CInputManager::GetInstance()->GetButtonDown(key)	
#define MOUSEPOS		CInputManager::GetInstance()->GetMousePos()