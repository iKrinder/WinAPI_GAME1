#pragma once
#include "Obj.h"

class Player :
    public Obj
{
private:
    Move_Dir dir;
    Obj* pMonster;
    Obj* pBullet;
    list<Obj*> pBList;
    DWORD time;
    DWORD dashtime;
    bool dashflag;
    DWORD delaytime;
    
public:
    void Initialize() override;
    void Progress() override;
    void Render(HDC hdc) override;
    void Release() override;

    void SetMonster(Obj* _pMonster);
    void KeyCheck();
    list<Obj*>* GetBullet();
public:
    Player();
    Player(double _x, double _y);
    ~Player();
};