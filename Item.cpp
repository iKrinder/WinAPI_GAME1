#include "Item.h"

Item::Item()
{

}

Item::~Item()
{

}

void Item::Initialize()
{
	info.size_x = 10;
	info.size_y = 10;

}

void Item::Progress()
{
	
}

void Item::Render(HDC hdc)
{
	Rectangle(hdc,
		info.x - info.size_x,
		info.y - info.size_y,
		info.x + info.size_x,
		info.x + info.size_y);

	TCHAR str[50];
	wsprintf(str, TEXT("Item"));
	TextOut(hdc, info.x - 2, info.y + 2, str ,lstrlen(str));
}

void Item::Release()
{
}