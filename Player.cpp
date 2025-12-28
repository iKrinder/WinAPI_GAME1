#include "Player.h"
#include "Bullet.h"
#include "ObjManager.h"

Player::Player()
{

}

Player::Player(double _x, double _y)
	:Obj(_x, _y)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	info.x = 100;
	info.y = 100;
	angle = 0;
	time = GetTickCount();
	dashtime = GetTickCount();
	dashflag = false;
	hp = 15;

	info.size_x = 50;
	info.size_y = 50;

	frame.dwTime = GetTickCount();

	SetMotion(0, 0, 0, 0, 0);
	dir = Dir_End;

}

void Player::Progress()
{
	if (frame.dwTime + 100 < GetTickCount())
	{
		frame.dwTime = GetTickCount();
		FrameMove();
	}
	KeyCheck();
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	INFO tinfo;
	tinfo.x = pt.x;
	tinfo.y = pt.y;

	CheckDir(tinfo);
}

void Player::Render(HDC _hdc)
{

	TCHAR str[50];
	wsprintf(str, TEXT("x: %d, y: %d"), (int)info.x, (int)info.y);
	TextOut(_hdc, info.x - 40, info.y - 40, str, lstrlen(str));

	wsprintf(str, TEXT("angle: %d"), (int)angle);
	TextOut(_hdc, 20, 10, str, lstrlen(str));

	MoveToEx(_hdc, info.x, info.y, 0);

	double x = info.x + cos(angle * PI / 180) * 30;
	double y = info.y + -sin(angle * PI / 180) * 30 * flagY;

	LineTo(_hdc, x, y);

	TransparentBlt(_hdc,
		int(info.x - info.size_y / 2),
		int(info.y - info.size_y / 2),
		(int)info.size_x,
		(int)info.size_y,
		(*m_pVecBMP)[BMP_STAGE_PLAYER]->GetMemDC(),
		int(info.size_x * frame.iStartX),
		int(info.size_y * frame.iStartY),
		(int)info.size_x,
		(int)info.size_y,
		RGB(255, 1, 255));

}

void Player::Release()
{

}

void Player::SetMonster(Obj* _pMonster)
{
	pMonster = _pMonster;
}

void Player::KeyCheck()
{
	if (angle <= 180 && angle >= 135)
	{
		dir = Dir_Left;
		SetMotion(2, 0, 2, 2, 2);
	}

	if (0 <= angle && angle <= 45)
	{
		dir = Dir_Right;
		SetMotion(0, 0, 0, 2, 0);
	}

	if (45 < angle && angle < 135 && flagY == -1)
	{
		dir = Dir_Bottom;
		SetMotion(3, 0, 3, 2, 3);
	}

	if (45 < angle && angle < 135 && flagY == 1)
	{
		dir = Dir_Top;
		SetMotion(1, 0, 1, 2, 1);
	}

	if (GetAsyncKeyState('W'))
	{
		if ((info.y - 75) > 0)
		{
			info.y -= 7;
		}
	}
	if (GetAsyncKeyState('A'))
	{
		if ((info.x - 75) > 0)
		{
			info.x -= 7;
		}
		
	}

	if (GetAsyncKeyState('S'))
	{
		if ((info.y + 75) < 600)
		{
			info.y += 7;
		}
		
	}

	if (GetAsyncKeyState('D'))
	{
		if ((info.x + 75) < 800)
		{
			info.x += 7;
		}
		
	}


	if (GetAsyncKeyState('F'))
	{
		angle += 10;

		if (angle >= 360)
		{
			angle -= 360;
		}
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (dashtime + 500 > GetTickCount() && dashflag)
		{
			MoveDir(20);
			dashtime = GetTickCount();
		}
		
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (time + 250 < GetTickCount())
		{
			
			Obj* temp = new Bullet;
			temp->SetPos(info);

			temp->SetFlagY(flagY);
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 3);
			

			temp->SetAngle(angle);
			((Bullet*)temp)->ChangeSpeed(20);
			ObjManager::GetInst()->AddOBJ(bullet_, temp);

			
			/*
			temp->Initialize();
			temp->SetPos(info);
			pBList.push_back(temp);
			pBList.back()->SetAngle(angle);
			time = GetTickCount();
			*/
		}

	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		
	}
}