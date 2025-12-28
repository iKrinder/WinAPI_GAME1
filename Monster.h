#pragma once
#include "Obj.h"
#include <random>

class Monster :
    public Obj
{
protected:
public:
    virtual void Initialize() override = 0;
    virtual void Progress() override = 0;
    virtual void Render(HDC hdc) override = 0;
    void Release() override;
    virtual Monster_Type Checktype() = 0;
    void Move(int _speed);
    virtual void Attack() = 0;
public:
    Monster();
    Monster(double _x, double _y);
    ~Monster();
};

