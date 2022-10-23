#include "framework.h"
#include "CResourceManager.h"

#include "CPathManager.h"
#include "CImage.h"

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

CImage* CResourceManager::FindImg(const wstring& key)
{
	auto iter = m_umapImage.find(key);
	if (iter == m_umapImage.end())
		return nullptr;
	else
		return m_umapImage[key];
}

CImage* CResourceManager::LoadImg(const wstring& key, const wstring& fileName)
{
	CImage* pImage = FindImg(key);
	if (nullptr != pImage)
		return pImage;

	wstring filePath = GETPATH + fileName;
	pImage = new CImage;
	pImage->Load(filePath);
	pImage->SetKey(key);
	pImage->SetPath(filePath);
	m_umapImage.insert(make_pair(key, pImage));

	return pImage;
}

void CResourceManager::Init()
{
}

void CResourceManager::Release()
{
	for (pair<wstring, CImage*> texture : m_umapImage)
	{
		delete texture.second;
	}
	m_umapImage.clear();
}
