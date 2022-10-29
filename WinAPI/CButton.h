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

	// final : ���̻� �ڽ��� ������ �Ҽ� ������ ����
	// �θ��� ������ ��ɸ��� ����ϵ��� ����
	// ��ư�� ��� Ŭ���Ͽ� �����ϱ� ���� �뵵�θ� ���
	void OnMouseEnter() final;
	void OnMouseOver() final;
	void OnMouseExit() final;
	void OnMouseUp() final;
	void OnMouseDown() final;
	void OnMouseClicked() final;

	// delete : ���̻� �ش��Լ��� ��� �Ҽ� ������ ����
	// �θ𿡼� ������ ����� �ڽ��� ������� �ʱ⸦ �ٶ���� ���
	void AddChildUI(CUI* pChildUI) = delete;
};

