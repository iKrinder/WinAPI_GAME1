#include "GiantMonster.h"
#include "DefaultMonster.h"
#include "Bullet.h"
#include "ObjManager.h"
GiantMonster::GiantMonster()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(50, 550);


	info.x = 750;
	info.y = dis(gen);
}

void GiantMonster::Initialize()
{
	info.size_x = 40;
	info.size_y = 40;
	hp = 400;
	bmpSizeX = 32;
	bmpSizeY = 32;
	BALPA = GetTickCount();
	delayTime = GetTickCount();
	frame.dwTime = GetTickCount();
	SetMotion(2, 1, 4, 1, 2);
}

void GiantMonster::Progress()
{
	Move(1);
	Attack();

	if (frame.dwTime + 100 < GetTickCount())
	{
		FrameMove();

		frame.dwTime = GetTickCount();
	}

}

void GiantMonster::Render(HDC _hdc)
{
	TCHAR str[50];
	wsprintf(str, TEXT("HP: %d"), (int)hp);
	TextOut(_hdc, info.x, info.y, str, lstrlen(str));

	TransparentBlt(_hdc,
		int(info.x - info.size_y / 2),
		int(info.y - info.size_y / 2),
		(int)info.size_x,
		(int)info.size_y,
		(*m_pVecBMP)[BMP_STAGE_MONSTER]->GetMemDC(),
		int(bmpSizeX * frame.iStartX),
		int(bmpSizeY * frame.iStartY + 130),
		(int)bmpSizeX,
		(int)bmpSizeY,
		RGB(255, 1, 255));
}

void GiantMonster::Release()
{

}

void GiantMonster::Attack()
{
	if(GetTickCount() > BALPA + 999)
	{
		BALPA = GetTickCount();
		Obj* temp = new Bullet;
		((Bullet*)temp)->SetType(GMb_);
		temp->SetPos(info);
		CheckDir(ObjManager::GetInst()->GetObj(player_)->GetINFO());
		temp->SetAngle(angle);
		temp->SetFlagY(flagY);
		((Bullet*)temp)->ChangeSpeed(7);
		ObjManager::GetInst()->AddOBJ(mbullet_, temp);
	}
}

Monster_Type GiantMonster::Checktype()
{
	return Giant_;
}