#pragma once
#include "Defines.h"
#include "StateObj.h"
class StateManager
{
	static StateManager* inst;
public:
	static StateManager* GetInst()
	{
		if (inst == nullptr)
		{
			inst = new StateManager;
		}
		return inst;
	}
private:
	StateObj* state;
public:
	StateObj* GetState() { return state; }
	void SetState(State_Type _type);

	void Initialize();
	void Progress();
	void Render(HDC _hdc);
	void Release();
private:
	StateManager();
	~StateManager();
};

