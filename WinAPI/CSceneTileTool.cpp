#include "framework.h"
#include "CSceneTileTool.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"

#include "CTile.h"

LRESULT CALLBACK    WinTileToolProc(HWND, UINT, WPARAM, LPARAM);

CSceneTileTool::CSceneTileTool()
{
	m_hWndTileTool = 0;
	m_iTileSizeX = 0;
	m_iTileSizeY = 0;
	m_fScrollSpeed = 300;
}

CSceneTileTool::~CSceneTileTool()
{
}

void CSceneTileTool::SetTileIndex(UINT index)
{
	Vector vecMousePos = MOUSEWORLDPOS;
	float tilePosX = vecMousePos.x / CTile::TILESIZE;
	float tilePosY = vecMousePos.y / CTile::TILESIZE;

	// 타일이 없는 위치일 경우 무시
	if (tilePosX < 0.f || (int)m_iTileSizeX <= tilePosX ||
		tilePosY < 0.f || (int)m_iTileSizeY <= tilePosY)
		return;

	const list<CGameObject*>& listTile = GetLayerObject(Layer::Tile);
	for (CGameObject* pGameObject : listTile)
	{
		CTile* pTile = dynamic_cast<CTile*>(pGameObject);
		if (pTile->GetTilePosX() != (int)tilePosX ||
			pTile->GetTilePosY() != (int)tilePosY)
			continue;

		pTile->SetTileIndex(pTile->GetTileIndex() + index);
		return;
	}
}

void CSceneTileTool::CameraMove()
{
	Vector dir;
	if (BUTTONSTAY('A'))
	{
		dir.x = -1;
	}
	else if (BUTTONSTAY('D'))
		dir.x = 1;
	else dir.x = 0;

	if (BUTTONSTAY('W'))
		dir.y = -1;
	else if (BUTTONSTAY('S'))
		dir.y = 1;
	else
		dir.y = 0;

	CAMERA->Scroll(dir, m_fScrollSpeed);
}

void CSceneTileTool::SaveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iTileSizeX;
	UINT yCount = m_iTileSizeY;

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	for (CGameObject* pGameObject : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = dynamic_cast<CTile*>(pGameObject);
		pTile->Save(pFile);
	}

	fclose(pFile);
}

void CSceneTileTool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd;					// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CSceneTileTool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CSceneTileTool::Init()
{
	CTile* pTile1 = new CTile;
	pTile1->SetTileIndex(1);
	pTile1->SetTilePos(1, 1);
	AddGameObject(pTile1);
}

void CSceneTileTool::Enter()
{
	// DialogBox : 모달방식 (창이 포커싱이 잃지 않도록 제한함)
	// CreateDialog : 모달리스 방식 (창이 포커싱 제한을 하지 않음)
	m_hWndTileTool = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILETOOLBOX), hWnd, WinTileToolProc);
	ShowWindow(m_hWndTileTool, SW_SHOW);

	RECT rect;
	GetWindowRect(m_hWndTileTool, &rect);
	MoveWindow(m_hWndTileTool, WINSTARTX + WINSIZEX, WINSTARTY,
		rect.right - rect.left, rect.bottom - rect.top, true);

	CreateTiles(10, 10);
}

void CSceneTileTool::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GroupScene::Title);
	}

	if (LMOUSEDOWN(false))
	{
		SetTileIndex(1);
	}

	CameraMove();
}

void CSceneTileTool::Render()
{
}

void CSceneTileTool::Exit()
{
	EndDialog(m_hWndTileTool, IDOK);

	DeleteAll();
}

void CSceneTileTool::Release()
{
}

LRESULT CALLBACK    WinTileToolProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_TILEBUTTON)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDITTILEXSIZE, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDITTILEYSIZE, nullptr, false);

			CScene* pCurScene = SCENE->GetCurScene();
			pCurScene->CreateTiles(x, y);
		}
		else if (LOWORD(wParam) == IDC_BUTTONTILESAVE)
		{
			CScene* pCurScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = dynamic_cast<CSceneTileTool*>(pCurScene);
			assert(nullptr != pTileToolScene && L"TileTool Scene cast Failed");

			pTileToolScene->SaveTileData();
		}
		else if (LOWORD(wParam) == IDC_BUTTONTILELOAD)
		{
			CScene* pCurScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = dynamic_cast<CSceneTileTool*>(pCurScene);
			assert(nullptr != pTileToolScene && L"TileTool Scene cast Failed");

			pTileToolScene->LoadTileData();
		}
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}