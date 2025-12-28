#include "StateManager.h"
#include "MainMenu.h"
#include "Stage.h"

StateManager* StateManager::inst = nullptr;

StateManager::StateManager()
{
}

StateManager::~StateManager()
{

}

void StateManager::Initialize()
{
	state = nullptr;
}

void StateManager::Progress()
{
	if (state == nullptr)
	{
		return;
	}
	state->Progress();
}

void StateManager::Render(HDC _hdc)
{
	if (state == nullptr)
	{
		return;
	}
	state->Render(_hdc);
}

void StateManager::Release()
{
	if (state != nullptr)
	{
		delete state;
		state = nullptr;
	}
}

void StateManager::SetState(State_Type _type)
{
	if (state)
	{
		delete state;
		state = nullptr;
	}

	switch (_type)
	{
	case menu_:
		state = new MainMenu;
		break;
	case stage_:
		state = new Stage;
		break;
	case logo_:
		break;
	}
	state->Initialize();
}