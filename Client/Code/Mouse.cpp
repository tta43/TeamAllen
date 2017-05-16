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
	// ���� ���콺 Ŀ���� ��ǥ�� ������ �Լ�.
	GetCursorPos(&ptMouse);

	// ���� ��ü â�� ���� ���콺�� ��ǥ�� �ش� ������ â ���� ���� ��ǥ�� ��ȯ���ִ� �Լ�.
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

	// 3���� ��ǥ��� ����	

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
