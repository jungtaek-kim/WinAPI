#pragma once

class CCore;
class CImage;

class CResourceManager : public SingleTon<CResourceManager>
{
	friend SingleTon<CResourceManager>;
	friend CCore;
private:
	CResourceManager();
	virtual ~CResourceManager();

private:
	unordered_map<wstring, CImage*> m_umapTexture;

public:
	CImage* FindImg(const wstring& key);
	CImage* LoadImg(const wstring& key, const wstring& fileName);

private:
	void Init();
	void Release();
};

#define RESOURCE	CResourceManager::GetInstance()
