#pragma once
#include "Defines.h"
#include "Obj.h"

class StateObj
{
protected:
	vector<CLoadBMP*> m_vecBMP;
public:
	virtual void Initialize() = 0;
	virtual void Progress() = 0;
	virtual void Render(HDC _hdc) = 0;
	virtual void Release() = 0;

	virtual ~StateObj() {};
};

