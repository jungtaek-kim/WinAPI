#pragma once
#include "CResource.h"
class CImage : public CResource
{
private:
	HDC		m_hdc;		// ��Ʈ���̹����� �׸��� ���� DC
	HBITMAP	m_hBmp;		// ��Ʈ���̹����� �ڵ鰪
	BITMAP	m_bmpInfo;	// ��Ʈ���̹����� ����

public:
	CImage();
	virtual ~CImage();

	HDC GetImgDC();
	BITMAP GetBmpInfo();
	int GetBmpWidth();
	int GetBmpHeight();

	void Load(const wstring& filePath);
};

