#pragma once

#include "Engine_Include.h"

BEGIN(Engine)

class CLayer;
class CComponent;

class ENGINE_DLL CScene
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CScene(void);

public:
	virtual HRESULT	InitScene(void);
	virtual void	Update(void);
	virtual void	Render(void);

private:
	virtual void	Release(void);

public:
	const CComponent* GetComponent(WORD LayerID, const wstring& wstrObjKey, const wstring& wstrComponentKey);

protected:
	LPDIRECT3DDEVICE9		m_pDevice;

protected:
	typedef map<WORD, CLayer*>		MAPLAYER;
	MAPLAYER		m_mapLayer;

};

END