#include "Mouse.h"

IMPLEMENT_SINGLETON(Engine::CMouse)

Engine::CMouse::CMouse(void)
{
	m_xPos = GetMousePos().x;
}

Engine::CMouse::~CMouse(void)
{
}

D3DXVECTOR3 Engine::CMouse::GetMousePos(void)
{
	static POINT ptMouse;
	// 현재 마우스 커서의 좌표를 얻어오는 함수.
	GetCursorPos(&ptMouse);

	// 현재 전체 창에 대한 마우스의 좌표를 해당 윈도우 창 영역 안의 좌표로 변환해주는 함수.
	ScreenToClient(m_hWnd, &ptMouse);

	return D3DXVECTOR3((float)ptMouse.x, (float)ptMouse.y, 0.f);
}


D3DXVECTOR3 Engine::CMouse::GetWorldMousePos(float fWinCX, float fWinCY, D3DXMATRIX matProj)
{
	D3DXVECTOR3 vMouse = GetMousePos();
	D3DXVECTOR3 vResult;

	vResult.x = (vMouse.x * 2.f / fWinCX) - 1.f;
	vResult.y = -(vMouse.y * 2.f / fWinCY) + 1.f;
	vResult.z = 0.f;

	D3DXMATRIX matInvProj;
	D3DXMatrixInverse(&matInvProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vResult, NULL, &matInvProj);

	// 3차원 좌표계로 변경	

	return vResult;
}

float Engine::CMouse::GetMouseGap(void)
{
	return GetMousePos().x - m_xPos;
}

void Engine::CMouse::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
}
