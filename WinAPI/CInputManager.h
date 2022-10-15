#pragma once

class CCore;

class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
	friend CCore;
private:
	CInputManager();
	virtual ~CInputManager();

	static const int VKEY_SIZE = 0xFF;	// VK�� �ִ� ����

	bool m_arrPrevKey[VKEY_SIZE];		// ���� Ű�� �Է»���
	bool m_arrCurKey[VKEY_SIZE];		// ���� Ű�� �Է»���
	POINT m_ptMousePos;					// ���� ���콺 ��ġ

	void Init();
	void Update();
	void Release();

public:

	bool GetButton(const int key);		// Ű�� ������ �ִ� ��
	bool GetButtonUp(const int key);	// Ű�� �ö� ����
	bool GetButtonDown(const int key);	// Ű�� ������ ����
	POINT GetMousePos();				// ���� ���콺 ��ġ
};

#define	INPUT			CInputManager::GetInstance()
#define BUTTONSTAY(key)	CInputManager::GetInstance()->GetButton(key)
#define BUTTONUP(key)	CInputManager::GetInstance()->GetButtonUp(key)	
#define BUTTONDOWN(key)	CInputManager::GetInstance()->GetButtonDown(key)	
#define MOUSEPOS		CInputManager::GetInstance()->GetMousePos()