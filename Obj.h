#pragma once
#include "Defines.h"
#include "LoadBMP.h"

class Obj
{
protected:
	INFO info;
	double angle;
	int flagY;
	RECT rc;
	int hp;

	int bmpSizeX, bmpSizeY;

	//image
	static vector<CLoadBMP*>* m_pVecBMP;

	FRAME frame;
	int m_iStartMotionX;
	int m_iStartMotionY;
public:
	INFO GetINFO() { return info; }
	RECT GetRC();
	void ChangeHP(int _n) { hp += _n; }
	static void SetBMP(vector<CLoadBMP*>* pVecBMP)
	{
		m_pVecBMP = pVecBMP;
	}
	void FrameMove();
	void SetMotion(int _startX, int _startY, int _lastX, int _lastY, int iframeX);
public:
	virtual void Initialize() = 0;
	virtual void Progress() = 0;
	virtual void Render(HDC _hdc) = 0;
	virtual void Release() = 0;
public:
	void MoveDir(int speed);
	void CheckDir(INFO _targetInfo);
	void SetPos(INFO _info);
	void SetAngle(double _angle) { angle = _angle; }
	void SetFlagY(int _flagY);
	int GetHP() { return hp; }
public:
	Obj();
	Obj(double _x, double _y);
	virtual ~Obj();
};

