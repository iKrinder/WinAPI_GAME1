#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::Initialize()
{
	info.size_x = 40;
	info.size_y = 40;

	rc = GetRC();

	delaytime = GetTickCount();

	flag = false;
}

void Weapon::Progress()
{

	if (delaytime + 500 < GetTickCount())
	{
		delaytime = GetTickCount();

		flag = false;
	}
}

void Weapon::Render(HDC hdc)
{
	Ellipse(hdc,
		info.x - info.size_x,
		info.y - info.size_y,
		info.x + info.size_x,
		info.y + info.size_y);
}

void Weapon::Release()
{
}

void Weapon::IsActive(bool _flag)
{
	flag = _flag;
	delaytime = GetTickCount();
}