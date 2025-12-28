#pragma once
#include "Defines.h"

class Obj;

class MainGame
{
	HDC m_hdc;

public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
public:

	MainGame();
	~MainGame();
};

