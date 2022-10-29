#pragma once

class CCore;
class CUI;

class CUIManager : public SingleTon<CUIManager>
{
	friend SingleTon<CUIManager>;
	friend CCore;
private:
	CUIManager();
	virtual ~CUIManager();

private:
	void MouseEvent(CUI* pUI);

private:
	void Init();
	void Update();
	void Release();
};

#define UI	CUIManager::GetInstance()
