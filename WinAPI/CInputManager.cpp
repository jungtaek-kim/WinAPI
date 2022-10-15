#include "framework.h"
#include "CInputManager.h"

#include "WinAPI.h"

CInputManager::CInputManager()
{
	// Ű ���¸� ��� ������ ���� ���·� �ʱ�ȭ
	m_arrPrevKey[0] = { false };
	m_arrCurKey[0] = { false };
	m_ptMousePos = { 0, 0 };
}

CInputManager::~CInputManager()
{
}

void CInputManager::Init()
{
}

void CInputManager::Update()
{
	// ���� ����(Focus)�� �����찡 ���� �������ΰ��� Ȯ��
	if (hWnd != GetFocus())
	{
		// �����찡 ����(Focus)�� ���°� �ƴ� ��� Ű�Է��� ������Ŵ
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			m_arrPrevKey[key] = m_arrCurKey[key];
			m_arrCurKey[key] = false;
		}
		return;
	}

	// ��� Ű �����ŭ �ݺ��ϸ� �Է»��¸� Ȯ��
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];
		if (GetAsyncKeyState(key) & 0x8000)
		{
			m_arrCurKey[key] = true;
		}
		else
		{
			m_arrCurKey[key] = false;
		}
	}

	// GetCursorPos() �����쿡�� ����� �»�� ���� ���콺�� ��ǥ�� ��ȯ
	GetCursorPos(&m_ptMousePos);
	// ����� �»�� ���� ���콺 ��ǥ�� ���� ������ ���� ���콺 ��ġ�� ���
	ScreenToClient(hWnd, &m_ptMousePos);
}

void CInputManager::Release()
{
}

bool CInputManager::GetButton(const int key)
{
	// Ű�� ������ �ִ� ��
	return (true == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CInputManager::GetButtonUp(const int key)
{
	// Ű�� �ö� ����
	return (false == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CInputManager::GetButtonDown(const int key)
{
	// Ű�� ������ ����
	return (true == m_arrCurKey[key] && false == m_arrPrevKey[key]);
}

POINT CInputManager::GetMousePos()
{
	return m_ptMousePos;
}
