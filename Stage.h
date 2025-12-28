#pragma once
#include "StateObj.h"
class Stage :
    public StateObj
{
public:
    void Initialize() override;
    void Progress() override;
    void Render(HDC _hdc) override;
    void Release() override;

    Stage();
    ~Stage();
};

