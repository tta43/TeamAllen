/*!
* \file CameraObserver.h
* \date 2017/05/11 15:23
*
* \author Administrator
* Contact: user@company.com
*
* \brief
*
* TODO: long description
*
* \note
*/

#ifndef CameraObserver_h__
#define CameraObserver_h__

#include "Observer.h"

class CCameraObserver
	: public Engine::CObserver
{
private:
	CCameraObserver(void);

public:
	virtual ~CCameraObserver(void);

public:
	const D3DXMATRIX* GetView(void) { return &m_matView; }
	const D3DXMATRIX* GetProj(void) { return &m_matProj; }

public:
	virtual void Update(int message);

public:
	static CCameraObserver* Create(void);

private:
	D3DXMATRIX		m_matView;
	D3DXMATRIX		m_matProj;
};

#endif // CameraObserver_h__