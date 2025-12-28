#pragma once
#include "StateObj.h"

class MainMenu
	: public StateObj
{
	RECT startRC, exitRC;
	POINT startPT, exitPT;
	int backPosX, backPosX2;
	DWORD dwBackTime;
public:
	void Initialize() override;
	void Progress() override;
	void Render(HDC _hdc) override;
	void Release() override;

	MainMenu() {}
	~MainMenu() {}
};

