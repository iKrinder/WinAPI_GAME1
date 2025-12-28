#include "MainMenu.h"
#include "StateManager.h"

void MainMenu::Initialize()
{
	startPT.x = 512;
	startPT.y = 288;
	startRC.left = startPT.x - 75;
	startRC.right = startPT.x + 75;
	startRC.top = startPT.y - 75;
	startRC.bottom = startPT.y + 75;

	exitPT.x = 40;
	exitPT.y = 40;
	exitRC.left = exitPT.x - 30;
	exitRC.right = exitPT.x + 30;
	exitRC.top = exitPT.y - 30;
	exitRC.bottom = exitPT.y + 30;

	dwBackTime = GetTickCount();
	backPosX = 0;
	backPosX2 = -800;

	char temp[100];
	PTCHAR str = temp;

	strcpy(temp, "Texture/BackBuffer.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	strcpy(temp, "Texture/MainMenu/MenuBack/MenuBackGround.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	strcpy(temp, "Texture/MainMenu/Button/Start.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	strcpy(temp, "Texture/MainMenu/Button/Exit.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));


	Obj::SetBMP(&m_vecBMP);
}

void MainMenu::Progress()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (PtInRect(&startRC, pt))
		{
			StateManager::GetInst()->SetState(stage_);
		}
		if (PtInRect(&exitRC, pt))
		{
			StateManager::GetInst()->Release();
			DestroyWindow(g_hWnd);
		}
	}
}

void MainMenu::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
		0, 0, 1024, 576);*/
	/*Rectangle(_hdc,
		startRC.left, startRC.top, startRC.right, startRC.bottom);
	Rectangle(_hdc,
		exitRC.left, exitRC.top, exitRC.right, exitRC.bottom);*/

	BitBlt(m_vecBMP[BMP_MENU_BACKBUFFER]->GetMemDC(), 0 + backPosX, 0, WinSizeX, WinSizeY,
		m_vecBMP[BMP_MENU_BACK]->GetMemDC(), 0, 0, SRCCOPY);

	BitBlt(m_vecBMP[BMP_MENU_BACKBUFFER]->GetMemDC(), 0 + backPosX2, 0, WinSizeX, WinSizeY,
		m_vecBMP[BMP_MENU_BACK]->GetMemDC(), 0, 0, SRCCOPY);

	if (dwBackTime + 0 < GetTickCount())
	{
		++backPosX;
		++backPosX2;
		dwBackTime = GetTickCount();
	}

	if (backPosX > 800)
		backPosX = 0;
	if (backPosX2 > 0)
		backPosX2 = -800;


	

	TransparentBlt(m_vecBMP[BMP_MENU_BACKBUFFER]->GetMemDC(),
		startPT.x-75, startPT.y-75,
		150, 150,
		m_vecBMP[BMP_MENU_BUTTON_START]->GetMemDC(),
		150, 0,
		150, 150, RGB(255, 255, 255));
	TransparentBlt(m_vecBMP[BMP_MENU_BACKBUFFER]->GetMemDC(),
		exitPT.x-30, exitPT.y-30,
		70, 70,
		m_vecBMP[BMP_MENU_BUTTON_EXIT]->GetMemDC(),
		150, 0,
		150, 150, RGB(0, 255, 0));

	BitBlt(_hdc, 0, 0, WinSizeX, WinSizeY, m_vecBMP[BMP_MENU_BACKBUFFER]->GetMemDC(), 0, 0, SRCCOPY);



}

void MainMenu::Release()
{

}