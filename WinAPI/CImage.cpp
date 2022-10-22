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
		nullptr,								// hInstance. nullptr�� �ص� ��.
		filePath.c_str(),					// ���� ��θ� C style ���ڿ��� ��ȯ
		IMAGE_BITMAP,							// �̹��� Ÿ��, ��Ʈ�� �̹����� ����
		0, 0,									// �̹����� X, Y ũ��, 0�� �ָ� �̹��� ũ��� ����
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// �̹��� �ε� Ÿ��.
	);

	assert(m_hBmp);	// �̹����� ���ٸ� assert�� ���� ����

	m_hdc = CreateCompatibleDC(GETDC);	// ��Ʈ���̹����� ������ DC ����
	SelectObject(m_hdc, m_hBmp);		// ��Ʈ���̹����� DC ����
	GetObject(m_hBmp, sizeof(BITMAP), &m_bmpInfo);	// ��Ʈ���̹��� ���� ����
}