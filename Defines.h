#pragma once

#include <vector>
#include <list>
#include <map>
#include <ctime>
#include "framework.h"

#include <random>

#pragma comment(lib, "msimg32.lib")

#pragma warning(disable:4996)

using namespace std;

extern HWND g_hWnd;

const double PI = 3.1415926535897;

const int WinSizeX = 800;
const int WinSizeY = 600;

typedef struct tagInfo
{
	double x, y;
	double size_x, size_y;

public:
	tagInfo()
		:x(0), y(0), size_x(0), size_y(0)
	{

	}

	tagInfo(double _x, double _y)
		:x(_x), y(_y)
	{

	}

	tagInfo(double _x, double _y, double _size_x, double _size_y)
		:x(_x), y(_y), size_x(_size_x), size_y(_size_y)
	{
		
	}
}INFO;

typedef struct tagFrame
{
	int iStartX;
	int iStartY;
	int iLastX;
	int iLastY;
	DWORD dwTime;
}FRAME;

enum Obj_Type
{
	player_,
	monster_,
	bullet_,
	mbullet_,
	item_
};

enum Monster_Type
{
	Default_,
	Upgrade_,
	Giant_
};

enum Bullet_Type
{
	Pb_,
	DMb_,
	UMb_,
	GMb_,
};

enum State_Type
{
	logo_,
	menu_,
	stage_,
	end_,
};

enum MENU_BMP
{
	BMP_MENU_BACKBUFFER,
	BMP_MENU_BACK,
	BMP_MENU_BUTTON_START,
	BMP_MENU_BUTTON_EXIT,
	BMP_MENU_END,
};

enum STAGE_BMP
{
	BMP_STAGE_BACKBUFFER,
	BMP_STAGE_BACK,
	BMP_STAGE_PLAYER,
	BMP_STAGE_MONSTER,
	BMP_STAGE_BULLET,
	BMP_STAGE_END,
};

enum Move_Dir
{
	Dir_Left,
	Dir_Right,
	Dir_Top,
	Dir_Bottom,
	Dir_End,
};