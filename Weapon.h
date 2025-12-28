#pragma once
#include "Obj.h"
class Weapon :
    public Obj
{
    bool flag;
    DWORD delaytime;
public:
    void Initialize() override;
    void Progress() override;
    void Render(HDC hdc) override;
    void Release() override;
    void IsActive(bool _flag);
    Weapon();
    ~Weapon();
};

