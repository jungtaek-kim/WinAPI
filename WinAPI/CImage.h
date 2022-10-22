#pragma once
#include "CResource.h"
class CImage : public CResource
{
private:
	HDC		m_hdc;		// 비트맵이미지를 그리기 위한 DC
	HBITMAP	m_hBmp;		// 비트맵이미지의 핸들값
	BITMAP	m_bmpInfo;	// 비트맵이미지의 정보

public:
	CImage();
	virtual ~CImage();

	HDC GetImgDC();
	BITMAP GetBmpInfo();
	int GetBmpWidth();
	int GetBmpHeight();

	void Load(const wstring& filePath);
};

