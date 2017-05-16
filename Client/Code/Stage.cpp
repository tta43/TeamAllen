#include "stdafx.h"
#include "Stage.h"
#include "Include.h"
#include "Layer.h"
#include "Export_Function.h"
#include "Pipeline.h"
#include "Component.h"
#include "Transform.h"
#include "Frustum.h"

#include "Player.h"
#include "StaticCamera.h"
#include "Wall.h"
#include "Floor.h"
#include "Ceiling.h"
#include "Cube.h"

CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
	: Engine::CScene(pDevice)
	  ,m_iLightCount(0)
{
}

CStage::~CStage(void)
{
	Release();
}

void CStage::Update(void)
{
	// Frustum을 만든다.
	D3DXMATRIX matView;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProj;
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	CFrustumMgr::GetInstance()->MakeFrustumPlane(matView, matProj);

	Engine::CScene::Update();
}

void CStage::Render(void)
{
	Engine::CScene::Render();
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CStage*	pScene = new CStage(pDevice);
	if (FAILED(pScene->Initialize()))
		Safe_Delete(pScene);

	return pScene;
}

HRESULT CStage::Initialize(void)
{
	HRESULT		hr = NULL;

	hr = Add_Environment_Layer();	FAILED_CHECK(hr);
	hr = Add_GameLogic_Layer();		FAILED_CHECK(hr);
	hr = Add_UI_Layer();			FAILED_CHECK(hr);

	// 빛
	//Add_Light(D3DXVECTOR3(20.f, 40.f, 500.f));
	//Add_Light(D3DXVECTOR3(20.f, 40.f, 250.f));

	return S_OK;
}

HRESULT CStage::Add_Environment_Layer(void)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = NULL;

	// 큐브
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			pGameObject = CCube::Create(m_pDevice);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->SetPos(D3DXVECTOR3(j * 2.f, i * 2.f, 10.f));
			pLayer->AddObject(L"Cube", pGameObject);
		}
	}
	
	/*pGameObject = CFloor::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Floor", pGameObject);*/

	/*pGameObject = CWall::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Wall", pGameObject);

	pGameObject = CCeiling::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Ceiling", pGameObject);*/

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_ENVIROMENT, pLayer));

	return S_OK;
}

HRESULT CStage::Add_GameLogic_Layer(void)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = NULL;

	// 플레이어
	pGameObject = CPlayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Player", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_GAMELOGIC, pLayer));
	return S_OK;
}

HRESULT CStage::Add_UI_Layer(void)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	Engine::CGameObject* pGameObject = nullptr;

	// Static Camera
	Engine::CTransform* pTransform = (Engine::CTransform*)m_mapLayer[LAYER_GAMELOGIC]->GetComponent(L"Player", L"Transform");
	
	pGameObject = CStaticCamera::Create(m_pDevice, pTransform);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"StaticCamera", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_UI, pLayer));
	return S_OK;
}

void CStage::Add_Light(D3DXVECTOR3 vecPos)
{
	//////// 조명 //////////

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_POINT;

	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	D3DXVECTOR3 vecDir = { 10.f, -2.f, 30.f };
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Position = vecPos;
	light.Attenuation0 = 2.f;
	light.Range = 50.f;

	m_pDevice->SetLight(m_iLightCount, &light);
	m_pDevice->LightEnable(m_iLightCount, TRUE);
	m_iLightCount++;

	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CStage::Release(void)
{

}

