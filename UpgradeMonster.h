#pragma once
#include "Monster.h"

class UpgradeMonster :
    public Monster
{
    DWORD BALPA;
    DWORD delayTime;
public:
    UpgradeMonster();
    void Initialize() override;
    void Progress() override;
    void Render(HDC hdc) override;
    void Release() override;
    void Attack() override;
    Monster_Type Checktype() override;
};

