#include "Stage.h"
#include "ObjManager.h"
#include "Player.h"
#include "Item.h"

void Stage::Initialize()
{
	ObjManager::GetInst()->AddOBJ(player_, new Player);
	ObjManager::GetInst()->ChangeSC(0);
	ObjManager::GetInst()->AddOBJ(item_, new Item);

	char temp[100];
	PTCHAR str = temp;

	strcpy(temp, "Texture/BackBuffer.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	strcpy(temp, "Texture/Stage/StageBack/StageBack.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	strcpy(temp, "Texture/Stage/Player/Player3.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	strcpy(temp, "Texture/Stage/Monster/pacman.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	strcpy(temp, "Texture/Stage/Bullet/Bullet.bmp");
	m_vecBMP.push_back((new CLoadBMP)->LoadBMP(temp));

	Obj::SetBMP(&m_vecBMP);
}

void Stage::Progress()
{
	ObjManager::GetInst()->Progress();

	ObjManager::GetInst()->CollisionWBM();

	ObjManager::GetInst()->CollisionWPB();

	ObjManager::GetInst()->IfBulletOutOfRange();
}

void Stage::Render(HDC _hdc)
{
	/*Rectangle(_hdc, 0, 0, WinSizeX, WinSizeY);

	MoveToEx(_hdc, 10, 10, 0);
	LineTo(_hdc, 100, 100);*/

	ObjManager::GetInst()->Render(_hdc);

	BitBlt(m_vecBMP[BMP_STAGE_BACKBUFFER]->GetMemDC(), 0, 0, 800, 600,
		m_vecBMP[BMP_STAGE_BACK]->GetMemDC(),
		0, 0, SRCCOPY);

	ObjManager::GetInst()->Render(m_vecBMP[BMP_STAGE_BACKBUFFER]->GetMemDC());

	BitBlt(_hdc, 0, 0, WinSizeX, WinSizeY, m_vecBMP[BMP_STAGE_BACKBUFFER]->GetMemDC(), 0, 0, SRCCOPY);
}

void Stage::Release()
{
	ObjManager::GetInst()->Release();
}

Stage::Stage()
{

}

Stage::~Stage()
{
	Release();
}