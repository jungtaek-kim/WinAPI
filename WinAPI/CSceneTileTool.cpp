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

	// Ÿ���� ���� ��ġ�� ��� ����
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

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd;					// �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CSceneTileTool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd; // �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

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
	// DialogBox : ��޹�� (â�� ��Ŀ���� ���� �ʵ��� ������)
	// CreateDialog : ��޸��� ��� (â�� ��Ŀ�� ������ ���� ����)
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