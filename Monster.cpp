#include "Monster.h"

Monster::Monster()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(50, 550);

	
	info.x = 750;
	info.y = dis(gen);
}

Monster::~Monster()
{

}

void Monster::Initialize()
{
	info.size_x = 20;
	info.size_y = 20;
	hp = 300;
}

void Monster::Move(int _speed)
{
	info.x -= _speed;
}

void Monster::Progress()
{
	Move(4);
}

void Monster::Render(HDC _hdc)
{
	Rectangle(_hdc,
		info.x - info.size_x,
		info.y - info.size_y,
		info.x + info.size_x,
		info.y + info.size_y);

	TCHAR str[50];
	wsprintf(str, TEXT("HP: %d"), (int)hp);
	TextOut(_hdc, info.x, info.y, str, lstrlen(str));
}

void Monster::Release()
{

}