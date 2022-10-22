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
	auto iter = m_umapTexture.find(key);
	if (iter == m_umapTexture.end())
		return nullptr;
	else
		return m_umapTexture[key];
}

CImage* CResourceManager::LoadImg(const wstring& key, const wstring& fileName)
{
	CImage* pTexture = FindImg(key);
	if (nullptr != pTexture)
		return pTexture;

	wstring filePath = GETPATH + fileName;
	pTexture = new CImage;
	pTexture->Load(filePath);
	pTexture->SetKey(key);
	pTexture->SetPath(filePath);
	m_umapTexture.insert(make_pair(key, pTexture));

	return pTexture;
}

void CResourceManager::Init()
{
}

void CResourceManager::Release()
{
	for (pair<wstring, CImage*> texture : m_umapTexture)
	{
		delete texture.second;
	}
	m_umapTexture.clear();
}
