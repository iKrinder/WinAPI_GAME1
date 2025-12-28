#include "Obj.h"
vector<CLoadBMP*>* Obj::m_pVecBMP = nullptr;

Obj::Obj()
	:flagY(1)
{

}

Obj::Obj(double _x, double _y)
	:info(_x, _y), flagY(1)
{
	
}
void Obj::MoveDir(int speed)
{
	info.x += cos(angle * PI / 180) * speed;
	info.y -= sin(angle * PI / 180) * speed * flagY;
}

void Obj::CheckDir(INFO _targetInfo)
{
	double x = _targetInfo.x - info.x;
	double y = _targetInfo.y - info.y;

	double distance = sqrt(x * x + y * y);

	angle = acos(x / distance) * 180 / PI;

	if (info.y <= _targetInfo.y)
	{
		flagY = -1; //플레이어가 위에, 각도가 밑
	}

	else
	{
		flagY = 1; //플레이어가 밑에, 각도가 위
	}
}

void Obj::SetFlagY(int _flagY)
{
	flagY = _flagY;
}

Obj::~Obj()
{

}

void Obj::SetPos(INFO _info)
{
	info.x = _info.x;
	info.y = _info.y;
}

RECT Obj::GetRC()
{
	rc.left = info.x - info.size_x / 2;
	rc.top = info.y - info.size_y / 2;
	rc.right = info.x + info.size_x / 2;
	rc.bottom = info.y + info.size_y / 2;

	return rc;
}

void Obj::FrameMove()
{
	++frame.iStartX;

	if (frame.iStartX >= frame.iLastX)
	{
		frame.iStartX = m_iStartMotionX;
		++frame.iStartY;

		if (frame.iStartY >= frame.iLastY)
		{
			frame.iStartY = m_iStartMotionY;
		}
	}
}

void Obj::SetMotion(int _startX, int _startY, int _lastX, int _lastY, int iframeX)
{
	if (frame.iStartX != iframeX)
	{
		frame.iStartX = iframeX;
	}

	m_iStartMotionX = _startX;
	m_iStartMotionY = _startY;

	frame.iLastX = _lastX;
	frame.iLastY = _lastY;

	if (frame.iStartY < _startY)
	{
		frame.iStartY = _startY;
	}
}