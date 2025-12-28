#pragma once
#include "Obj.h"

class Item :
    public Obj
{
public:
    void Initialize() override;
    void Progress() override;
    void Render(HDC hdc) override;
    void Release() override;
    Item();
    ~Item();
};

