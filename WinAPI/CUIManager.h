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
	CUI* GetTopUI();
	CUI* GetTopChildUI(CUI* pUI);

	void MouseEvent(CUI* pUI, CUI* pTopChildUI);

private:
	void Init();
	void Update();
	void Release();
};

#define UI	CUIManager::GetInstance()
