#pragma once
#include "CUI.h"
class CButton : public CUI
{
public:
	CButton();
	virtual ~CButton();

private:
	Color m_colorRect;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	// final : 더이상 자식이 재정의 할수 없도록 막음
	// 부모의 고유의 기능만을 사용하도록 제한
	// 버튼의 경우 클릭하여 반응하기 위한 용도로만 사용
	void OnMouseEnter() final;
	void OnMouseOver() final;
	void OnMouseExit() final;
	void OnMouseUp() final;
	void OnMouseDown() final;
	void OnMouseClicked() final;

	// delete : 더이상 해당함수를 사용 할수 없도록 막음
	// 부모에서 정의한 기능을 자식은 사용하지 않기를 바랄경우 사용
	void AddChildUI(CUI* pChildUI) = delete;
};

