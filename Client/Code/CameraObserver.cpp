#include "stdafx.h"
#include "CameraObserver.h"
#include "Export_Function.h"

CCameraObserver::CCameraObserver(void)
{

}

CCameraObserver::~CCameraObserver(void)
{

}

void CCameraObserver::Update(int message)
{
	const list<void*>*		pDatalist = Engine::Get_InfoSubject()->GetDatalist(message);
	NULL_CHECK(pDatalist);

	switch (message)
	{
	case D3DTS_VIEW:
		m_matView = *((D3DXMATRIX*)pDatalist->front());
		break;

	case D3DTS_PROJECTION:
		m_matProj = *((D3DXMATRIX*)pDatalist->front());
		break;
	}
}

CCameraObserver* CCameraObserver::Create(void)
{
	return new CCameraObserver;
}

