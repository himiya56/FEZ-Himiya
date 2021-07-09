//=============================================================================
//
// オブジェクト管理処理 [manager.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "input.h"
#include "Keyboard.h"
#include "camera.h"
#include "light.h"

#include "testObj.h"
#include "player.h"
#include "collisiondetection.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInput = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CCollisionDetection *CManager::m_CollisionDetection = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//インスタンス生成・初期化処理
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	m_pInput = new CInputKeyboard;
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return -1;
	}

	// ライトの生成
	//m_pLight = new CLight;
	//if (FAILED(m_pLight->Init()))
	//{
	//	return E_FAIL;
	//}

	m_pCamera = CCamera::Create();

	// テクスチャの読み込み
	Load();

	//CTestObj::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CTestObj::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f));
	//CTestObj::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));

	m_CollisionDetection = CCollisionDetection::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f));

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f));

	return 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// 終了処理
	CObject::ReleaseAll();

	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		//メモリ破棄
		delete m_pInput;
		m_pInput = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		//メモリ破棄
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// テクスチャの破棄
	Unload();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// 更新処理
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// 描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// モデル・テクスチャ読み込み処理
//=============================================================================
void CManager::Load(void)
{
	CTestObj::Load();
}

//=============================================================================
// モデル・テクスチャ破棄処理
//=============================================================================
void CManager::Unload(void)
{
	CTestObj::Unload();
}
