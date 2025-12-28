#pragma once
#include "Defines.h"
class CLoadBMP
{
private:
	HDC m_hdc, m_MemDC;
	HBITMAP m_bitMap, m_oldbitMap;
public:
	HDC GetMemDC() { return m_MemDC; }

	CLoadBMP* LoadBMP(PTCHAR pFileName);
	void Release();

	CLoadBMP();
	~CLoadBMP();
};

