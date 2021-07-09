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
#include "fade.h"
#include "mode_title.h"
#include "mode_stage_select.h"
#include "mode_game.h"
#include "button_any.h"
#include "button_exit.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_stage1.h"
#include "button_stage2.h"
#include "button_stage3.h"

#include "testObj.h"
#include "player.h"
#include "collisiondetection.h"
#include "player_hook.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************

CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInput = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CManager::MODE  CManager::m_Mode = MODE_NONE;		//モード
bool CManager::m_bUseFade = false;					//フェードの使用状態
CSound * CManager::m_pSound = NULL;
CGameMode * CManager::m_pGameMode = NULL;
CFade * CManager::m_pFade = NULL;					//フェードへのポインタ


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
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	m_pCamera = CCamera::Create();
	//もしフェードのポインタがNULLの場合
	if (m_pFade == NULL)
	{
		//フェードの生成処理関数呼び出し
		m_pFade = CFade::Create(m_Mode);
	}
	// テクスチャの読み込み
	Load();

	CTestObj::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//CTestObj::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f));
	//CTestObj::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));

	CCollisionDetection::Create(D3DXVECTOR3(100.0f, 170.0f, 0.0f), PLAYER_SIZE, CCamera::ORIENTATION_FRONT);

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 170.0f, 0.0f), PLAYER_SIZE);

	// モードの設定
	SetMode(MODE_TITLE);

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
	//もしフェードのポインタがNULLではない場合
	if (m_pFade != NULL)
	{
		//フェードの終了処理関数呼び出し
		m_pFade->Uninit();
		//フェードのメモリ破棄
		delete m_pFade;
		//フェードのポインタをNULLにする
		m_pFade = NULL;
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
	//もしフェードされたら
	if (m_bUseFade == true)
	{
		//もしフェードのポインタがNULLではない場合
		if (m_pFade != NULL)
		{
			//フェードの更新処理関数呼び出し
			m_pFade->Update();
		}
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
// フェード開始処理関数
//=============================================================================
void CManager::StartFade(MODE mode)
{
	//モードを設定する
	m_Mode = mode;
	//フェードをする
	m_bUseFade = true;
}

//=============================================================================
// フェード停止処理関数
//=============================================================================
void CManager::StopFade(void)
{
	//フェードをやめる
	m_bUseFade = false;
}

//=============================================================================
// モード設定関数
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	//オブジェクトの全破棄処理関数呼び出し
	CObject::ReleaseAll();
	//モードを設定する
	m_Mode = Mode;
	//各モードの処理
	switch (m_Mode)
	{
	case MODE_TITLE:
		//タイトルモードの生成処理関数呼び出し
		CTitleMode::Create();
		break;
	case MODE_STAGE_SELECT:
		//ステージ選択モードの生成処理関数呼び出し
		CStageSelectMode::Create();
		break;
	case MODE_GAME_STAGE1:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_1);
		break;
	case MODE_GAME_STAGE2:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_2);
		break;
	case MODE_GAME_STAGE3:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_3);
		break;
	default:
		break;
	}
}

//=============================================================================
// モデル・テクスチャ読み込み処理
//=============================================================================
void CManager::Load(void)
{
	CTestObj::Load();
	CPlayerHook::Load();
	CAnyButton::TextureLoad();
	CExitButton::TextureLoad();
	CStartButton::TextureLoad();
	CTutorialButton::TextureLoad();
	CStage1Button::TextureLoad();
	CStage2Button::TextureLoad();
	CStage3Button::TextureLoad();
}

//=============================================================================
// モデル・テクスチャ破棄処理
//=============================================================================
void CManager::Unload(void)
{
	CTestObj::Unload();
	CPlayerHook::Unload();
	CAnyButton::TextureUnload();
	CExitButton::TextureUnload();
	CStartButton::TextureUnload();
	CTutorialButton::TextureUnload();
	CStage1Button::TextureUnload();
	CStage2Button::TextureUnload();
	CStage3Button::TextureUnload();
}
