#pragma once

#include "Engine_Include.h"

namespace Engine
{
	class CInputClass;
}

class CKeyMgr
{
public:
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr(void);
	~CKeyMgr(void);

public:
	bool StayKeyDown(BYTE nKey);
	bool OnceKeyDown(BYTE nKey);
	bool OnceKeyUp(BYTE nKey);

private:
	bool m_bKeyDown[256];
	bool m_bKeyUp[256];

	Engine::CInputClass* m_Input;
};