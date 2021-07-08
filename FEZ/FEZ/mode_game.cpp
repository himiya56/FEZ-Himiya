//=============================================================================
//
// ゲームモード [mode_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
//#include "sound.h"
#include "light.h"
#include "camera.h"
#include "keyboard.h"
//#include "joystick.h"
#include "mode_game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_bCreatePause = false;		//ポーズを使用してるか
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CGameMode * CGameMode::Create(STAGE stage)
{
	//ゲームモードのポインタ
	CGameMode * pGameMode = NULL;
	//もしゲームモードのポインタをNULLだった場合
	if (pGameMode == NULL)
	{
		//ゲームモードのメモリ確保
		pGameMode = new CGameMode;
		//もしゲームモードのポインタをNULLではない場合
		if (pGameMode != NULL)
		{
			pGameMode->m_Stage = stage;	//ステージの設定
			//ゲームモードの初期化関数呼び出し
			pGameMode->Init();
		}
	}
	//ゲームモードのポインタを返す
	return pGameMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//初期生成処理関数呼び出し(共通)
	InitCreate();
	//各ステージの生成
	InitStageCreate();
	////サウンドの取得
	//CSound * pSound = CManager::GetSound();
	////もしサウンドのポインタがnullptrではない場合
	//if (pSound != nullptr)
	//{
	//	//名前入力のBGM停止 
	//	pSound->StopSound(CSound::SOUND_LABEL_BGM_NAME);
	//}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameMode::Update(void)
{
	//入力処理関数呼び出し
	//Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CGameMode::InitCreate(void)
{
}

//=============================================================================
// 初期各ステージ生成処理関数
//=============================================================================
void CGameMode::InitStageCreate(void)
{
	switch (m_Stage)
	{
	case STAGE_1:
		break;
	case STAGE_2:
		break;
	case STAGE_3:
		break;
	default:
		break;
	}
}

//=============================================================================
// 入力処理関数
//=============================================================================
//void CGameMode::Input(void)
//{
//	//キーボードの取得
//	CKeyboard * pKeyboard = CManager::GetKeyboard();
//	//ジョイスティックの取得
//	CJoystick * pJoystick = CManager::GetJoystick();
//	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
//	DIJOYSTATE js;
//	//ジョイスティックの振動取得
//	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
//	if (lpDIDevice != NULL)
//	{
//		lpDIDevice->Poll();
//		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
//	}
//	//もしプレイヤーが死亡状態ではない場合
//	if (m_pPlayer->GetState() != CPlayer::STATE_DEATH)
//	{
//		//もしESCAPEキー又はジョイスティックのスタートボタンを押されたら
//		if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_START))
//		{
//			//もしポーズを使用していない場合
//			if (m_bCreatePause == false)
//			{
//				//ポーズボタンマネージャーの生成処理関数呼び出し
//				CPauseButtonManager::Create();
//			}
//		}
//	}
//}