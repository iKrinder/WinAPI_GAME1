#pragma once
#include "Defines.h"

class Obj;

class ObjManager
{
private:
	static ObjManager* inst;
public:
	static ObjManager* GetInst()
	{
		if (inst == nullptr)
		{
			inst = new ObjManager;
		}
		return inst;
	}
private:
	ObjManager();
	
private:
	map<Obj_Type, list<Obj*>> MapOBJ;

	int currentScore;
	int highScore;
	const char* saveFile;

public:
	int LoadHighScore(const char* filename);

	void SaveHighScore(const char* filename, int score);

	void AddOBJ(Obj_Type _type, Obj* _obj);
	
	Obj* GetObj(Obj_Type _type, int _n = 0);
	
	void Progress();

	void Render(HDC hdc);

	void Release();

	void CollisionWBM();

	void CollisionWPB();

	void IfBulletOutOfRange();

	void IfMonsterOutOfRange();

	void ChangeSC(int _sc) { currentScore = _sc; }
private:
	DWORD delayTime;
	DWORD delayTime2;
	DWORD delayTime3;
public:
	void CreateNormalMonster(DWORD _time);
	void CreateUpgradeMonster(DWORD _time);
	void CreateGiantMonster(DWORD _time);
};