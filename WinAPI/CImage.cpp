#include "framework.h"
#include "CImage.h"

#include "CRenderManager.h"

CImage::CImage()
{
	m_hdc = 0;
	m_hBmp = 0;
	m_bmpInfo = {};
}

CImage::~CImage()
{
	DeleteDC(m_hdc);
	DeleteObject(m_hBmp);
}

HDC CImage::GetImgDC()
{
	return m_hdc;
}

BITMAP CImage::GetBmpInfo()
{
	return m_bmpInfo;
}

int CImage::GetBmpWidth()
{
	return (int)(m_bmpInfo.bmWidth);
}

int CImage::GetBmpHeight()
{
	return (int)(m_bmpInfo.bmHeight);
}

void CImage::Load(const wstring& filePath)
{
	m_hBmp = (HBITMAP)LoadImage(
		nullptr,								// hInstance. nullptr로 해도 됨.
		filePath.c_str(),					// 파일 경로를 C style 문자열로 변환
		IMAGE_BITMAP,							// 이미지 타입, 비트맵 이미지로 지정
		0, 0,									// 이미지의 X, Y 크기, 0을 주면 이미지 크기로 설정
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// 이미지 로딩 타입.
	);

	assert(m_hBmp);	// 이미지가 없다면 assert를 통한 종료

	m_hdc = CreateCompatibleDC(GETDC);	// 비트맵이미지와 연결할 DC 생성
	SelectObject(m_hdc, m_hBmp);		// 비트맵이미지와 DC 연결
	GetObject(m_hBmp, sizeof(BITMAP), &m_bmpInfo);	// 비트맵이미지 정보 추출
}