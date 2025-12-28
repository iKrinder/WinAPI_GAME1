#include "ObjManager.h"
#include "DefaultMonster.h"
#include "UpgradeMonster.h"
#include "GiantMonster.h"
#include "StateManager.h"
#include <fstream>

ObjManager* ObjManager::inst = nullptr;

void ObjManager::CreateNormalMonster(DWORD _time)
{
	if (delayTime + _time < GetTickCount())
	{
		Obj* temp = new DefaultMonster;

		AddOBJ(monster_, temp);

		delayTime = GetTickCount();
	}
}

void ObjManager::CreateUpgradeMonster(DWORD _time)
{
	if (delayTime2 + _time < GetTickCount())
	{
		Obj* temp = new UpgradeMonster;

		AddOBJ(monster_, temp);

		delayTime2 = GetTickCount();
	}
}

void ObjManager::CreateGiantMonster(DWORD _time)
{
	if (delayTime3 + _time < GetTickCount())
	{
		Obj* temp = new GiantMonster;

		AddOBJ(monster_, temp);
		
		delayTime3 = GetTickCount();
	}
}

Obj* ObjManager::GetObj(Obj_Type _type, int _n)
{
	map<Obj_Type, list<Obj*>>::iterator iter;
	iter = MapOBJ.find(_type);
	Obj* t = nullptr;
	int cnt = 0;

	for (list<Obj*>::iterator iterList = iter->second.begin();
		iterList != iter->second.end(); ++iter, ++cnt)
	{
		if (cnt == _n)
		{
			t = *iterList;
			break;
		}

	}
	return t;
}

void ObjManager::AddOBJ(Obj_Type _type, Obj* _obj)
{
	map<Obj_Type, list<Obj*>>::iterator iter;
	iter = MapOBJ.find(_type);
	_obj->Initialize();

	if (iter == MapOBJ.end())
	{
		list<Obj*> t;
		t.push_back(_obj);
		MapOBJ.insert(pair<Obj_Type, list<Obj*>>(_type, t));
	}
	else
	{
		iter->second.push_back(_obj);
	}
}

void ObjManager::Progress()
{
	for (map<Obj_Type, list<Obj*>>::iterator iter = MapOBJ.begin();
		iter != MapOBJ.end(); ++iter)
	{
		for (list<Obj*>::iterator iterList = iter->second.begin();
			iterList != iter->second.end(); ++iterList)
		{
			(*iterList)->Progress();
		}
	}
	CreateNormalMonster(6500);
	CreateUpgradeMonster(7500);
	CreateGiantMonster(10500);
	IfMonsterOutOfRange();
}

ObjManager::ObjManager()
{
	delayTime = GetTickCount();
	delayTime2 = GetTickCount();
	delayTime3 = GetTickCount();

	currentScore = 0;
	highScore = 0;
	saveFile = "info.txt";
	highScore = LoadHighScore(saveFile);
}

void ObjManager::SaveHighScore(const char* _filename, int _score)
{
	ofstream outFile(_filename, ios::trunc);

	if (outFile.is_open())
	{
		outFile << _score;
		outFile.close();
	}
}

int ObjManager::LoadHighScore(const char* _filename)
{
	ifstream inFile(_filename);

	int highscore = 0;
	
	if (inFile.is_open())
	{
		inFile >> highscore;
		inFile.close();
	}

	return highscore;
}

void ObjManager::Release()
{
	for (map<Obj_Type, list<Obj*>>::iterator iter = MapOBJ.begin();
		iter != MapOBJ.end();)
	{
		for (list<Obj*>::iterator iterList = iter->second.begin();
			iterList != iter->second.end();)
		{
			delete (*iterList);
			(*iterList) = nullptr;

			iterList = iter->second.erase(iterList);
		}
		iter->second.clear();
		iter = MapOBJ.erase(iter);
	}
	MapOBJ.clear();

	SaveHighScore(saveFile, highScore);
}

void ObjManager::Render(HDC hdc)
{
	for (map<Obj_Type, list<Obj*>>::iterator iter = MapOBJ.begin();
		iter != MapOBJ.end(); ++iter)
	{
		for (list<Obj*>::iterator iterList = iter->second.begin();
			iterList != iter->second.end(); ++iterList)
		{

			(*iterList)->Render(hdc);
		}
	}

	TCHAR str[50];
	wsprintf(str, TEXT("Score: %d HighScore: %d"), currentScore, highScore);
	TextOut(hdc, 20, 40, str, lstrlen(str));
}

void ObjManager::IfBulletOutOfRange()
{
	map<Obj_Type, list<Obj*>>::iterator iter = MapOBJ.find(bullet_);

	if (iter == MapOBJ.end())
		return;

	for (list<Obj*>::iterator iterb = iter->second.begin(); iterb != iter->second.end();)
	{
		if (0 > (*iterb)->GetINFO().x || (*iterb)->GetINFO().x > 800 ||
			(*iterb)->GetINFO().y > 600 || (*iterb)->GetINFO().y < 0)
			{
				delete* iterb;
				*iterb = nullptr;
				iterb = iter->second.erase(iterb);
			}

		else
		{
			++iterb;
		}
	}
}

void ObjManager::IfMonsterOutOfRange()
{
	map<Obj_Type, list<Obj*>>::iterator iter = MapOBJ.find(monster_);

	if (iter == MapOBJ.end())
	{
		return;
	}

	for (list<Obj*>::iterator iterm = iter->second.begin(); iterm != iter->second.end();)
	{
		if (0 > (*iterm)->GetINFO().x)
		{
			delete* iterm;
			*iterm = nullptr;
			iterm = iter->second.erase(iterm);
		}

		else
		{
			++iterm;
		}
	}
}

void ObjManager::CollisionWBM()
{
	map<Obj_Type, list<Obj*>>::iterator iter = MapOBJ.find(bullet_);
	map<Obj_Type, list<Obj*>>::iterator iter2 = MapOBJ.find(monster_);

	if (iter == MapOBJ.end() || iter2 == MapOBJ.end())
	{
		return;
	}



	for (list<Obj*>::iterator iterm = iter2->second.begin(); iterm != iter2->second.end();)
	{
		bool mFlag = false;
		for (list<Obj*>::iterator iterb = iter->second.begin(); iterb != iter->second.end();)
		{
			RECT Brc, Mrc, rc;
			Mrc = (*iterm)->GetRC();
			Brc = (*iterb)->GetRC();

			if (IntersectRect(&rc, &Brc, &Mrc))
			{
				((Monster*)(*iterm))->ChangeHP(-3);

				delete (*iterb);
				(*iterb) = nullptr;
				iterb = iter->second.erase(iterb);
				if (((Monster*)(*iterm))->GetHP() <= 0)
				{
					delete* iterm;
					*iterm = nullptr;
					iterm = iter2->second.erase(iterm);
					mFlag = true;

					++currentScore;
					if (currentScore > highScore)
					{
						highScore = currentScore;
					}

					break;

				}

			}

			else
			{
				++iterb;
			}

			


		}
		if (!mFlag)
		{
			++iterm;
		}
	}
}

void ObjManager::CollisionWPB()
{
	map<Obj_Type, list<Obj*>>::iterator iter = MapOBJ.find(mbullet_);
	map<Obj_Type, list<Obj*>>::iterator iter2 = MapOBJ.find(player_);

	if (iter == MapOBJ.end() || iter2 == MapOBJ.end())
	{
		return;
	}
	
	for (list<Obj*>::iterator iterp = iter2->second.begin(); iterp != iter2->second.end();)
	{
		bool mflag = false;

		for (list<Obj*>::iterator iterb = iter->second.begin(); 
			iterb != iter->second.end();)
		{
			RECT rc, rcP, rcB;
			rcP = (*iterp)->GetRC();
			rcB = (*iterb)->GetRC();

			if (IntersectRect(&rc, &rcP, &rcB))
			{
				delete (*iterb);
				(*iterb) = nullptr;
				iterb = iter->second.erase(iterb);

				(*iterp)->ChangeHP(-5);

				if ((*iterp)->GetHP() <= 0)
				{
					delete* iterp;
					*iterp = nullptr;

					iterp = iter2->second.erase(iterp);

					mflag = true;
					break;
				}
				
			}
			else if (0 > (*iterb)->GetINFO().x || (*iterb)->GetINFO().x > 800 ||
				(*iterb)->GetINFO().y > 600 || (*iterb)->GetINFO().y < 0)
			{
				delete* iterb;
				*iterb = nullptr;
				iterb = iter->second.erase(iterb);

			}
			else
			{
				++iterb;
			}
			
		}
		if (!mflag)
		{
			++iterp;
		}
	}

	if (iter2->second.empty())
	{
		StateManager::GetInst()->SetState(menu_);
	}
}