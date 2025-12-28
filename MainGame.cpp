#include "MainGame.h"
#include "StateManager.h"


MainGame::MainGame()
{

}

MainGame::~MainGame()
{

}

void MainGame::Initialize()
{
	srand(unsigned int(time(NULL)));
	m_hdc = GetDC(g_hWnd);

	StateManager::GetInst()->Initialize();
	StateManager::GetInst()->SetState(menu_);

	//ObjManager::GetInst()->AddOBJ(player_, new Player);
	//ObjManager::GetInst()->AddOBJ(monster_, new DefaultMonster);
	//ObjManager::GetInst()->AddOBJ(monster_, new UpgradeMonster);

	/*
	//player 梓端 持失
	player = new Player(200, 300);
	player->Initialize();

	//monster 梓端 持失
	monster = new Monster(100, 500);
	monster->Initialize();

	//bullet 梓端 持失
	bullet = ((Player*)player)->GetBullet();

	//pMonster
	((Player*)player)->SetMonster(monster);*/
}

void MainGame::Progress()
{
	StateManager::GetInst()->Progress();

	//ObjManager::GetInst()->Progress();

	//ObjManager::GetInst()->CollisionWBM();
}

void MainGame::Render()
{
	/*Rectangle(m_hdc, 0, 0, 1024, 576);*/

	//MoveToEx(m_hdc, 10, 10, 0);
	//LineTo(m_hdc, 100, 100);
	//MoveToEx(m_hdc, 50, 20, 0);
	//LineTo(m_hdc, 100, 100);
	//MoveToEx(m_hdc, 10, 10, 0);
	//LineTo(m_hdc, 50, 20);

	//ObjManager::GetInst()->Render(m_hdc);
	StateManager::GetInst()->Render(m_hdc);
}

void MainGame::Release()
{
	//ObjManager::GetInst()->Release();
	StateManager::GetInst()->Release();
}