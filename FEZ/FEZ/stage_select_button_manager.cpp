//=============================================================================
//
// ステージ選択ボタンマネージャー [stage_select_button_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
//#include "sound.h"
#include "keyboard.h"
//#include "joystick.h"
#include "stage_select_button_manager.h"
#include "button_stage1.h"
#include "button_stage2.h"
#include "button_stage3.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE1_BUTTON_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))							//ステージ1ボタンの位置
#define STAGE2_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	//ステージ2ボタンの位置
#define STAGE3_BUTTON_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))							//ステージ3ボタンの位置
#define INPUT_INTERVAL (10)																//入力間隔

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelectButtonManager::CStageSelectButtonManager(OBJ_TYPE nObjectType) : CObject(nObjectType)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_nInputCount = 0;								//入力間隔
}

//=============================================================================
// デストラクタ
//=============================================================================
CStageSelectButtonManager::~CStageSelectButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CStageSelectButtonManager * CStageSelectButtonManager::Create(void)
{
	//ステージ選択ボタンマネージャーのポインタ
	CStageSelectButtonManager * pStageSelectButtonManager = NULL;
	//ステージ選択ボタンマネージャーのポインタNULLの場合
	if (pStageSelectButtonManager == NULL)
	{
		//ステージ選択ボタンマネージャーのメモリ確保
		pStageSelectButtonManager = new CStageSelectButtonManager;
		//ステージ選択ボタンマネージャーのポインタがNULLではない場合
		if (pStageSelectButtonManager != NULL)
		{
			//ステージ選択ボタンマネージャーの初期化処理関数呼び出し
			pStageSelectButtonManager->Init();
		}
	}
	//ステージ選択ボタンマネージャーのポインタを返す
	return pStageSelectButtonManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CStageSelectButtonManager::Init(void)
{
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = BUTTON_STAGE1;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CStageSelectButtonManager::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CStageSelectButtonManager::Update(void)
{
	//選択処理関数呼び出し
	Select();
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CStageSelectButtonManager::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CStageSelectButtonManager::Input(void)
{
	//キーボードの取得
	CInputKeyboard * pKeyboard = CManager::GetInput();
	////ジョイスティックの取得
	//CJoystick * pJoystick = CManager::GetJoystick();
	//LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	//DIJOYSTATE js;
	////ジョイスティックの振動取得
	//LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	//if (lpDIDevice != NULL)
	//{
	//	lpDIDevice->Poll();
	//	lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	//}
	//左矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT))
	{
		//現在のボタンを減算する
		m_nButton--;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
	}
	////上矢印ボタンか上スティックが入力された場合
	//if (lpDIDevice != NULL &&js.rgdwPOV[0] == 0 || lpDIDevice != NULL &&js.lY == -1000)
	//{
	//	//入力間隔を加算する
	//	m_nInputCount++;
	//	if (m_nInputCount % INPUT_INTERVAL == 0)
	//	{
	//		//現在のボタンを減算する
	//		m_nButton--;
	//		//ボタンの選択時音再生処理関数呼び出し
	//		m_apButton[m_nButton]->SelectSound();
	//	}
	//}
	//右矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT))
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
	}
	////下矢印ボタンか下スティックが入力された場合
	//if (lpDIDevice != NULL &&js.rgdwPOV[0] == 18000 || lpDIDevice != NULL &&js.lY == 1000)
	//{
	//	//入力間隔を加算する
	//	m_nInputCount++;
	//	if (m_nInputCount % INPUT_INTERVAL == 0)
	//	{
	//		//現在のボタンを減算する
	//		m_nButton++;
	//		//ボタンの選択時音再生処理関数呼び出し
	//		m_apButton[m_nButton]->SelectSound();
	//	}
	//}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN)/* || pJoystick->GetJoystickTrigger(JS_A)*/)
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
	}
}

//=============================================================================
// 選択処理関数
//=============================================================================
void CStageSelectButtonManager::Select(void)
{
	//もし現在のボタンがステージ1ボタンより下だったら
	if (m_nButton < BUTTON_STAGE1)
	{
		//現在のボタンをステージ3ボタンにする
		m_nButton = BUTTON_STAGE3;
	}
	//もし現在のボタンがステージ3ボタンを越えたら
	if (m_nButton > BUTTON_STAGE3)
	{
		//現在のボタンをステージ1ボタンにする
		m_nButton = BUTTON_STAGE1;
	}
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//ボタンの選択されてない時の色変更処理関数呼び出し
		m_apButton[nCount]->NotSelectColor();
	}
	//ボタンの選択時色変更処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
}

//=============================================================================
// キャンセル時音再生処理関数
//=============================================================================
void CStageSelectButtonManager::CancelSound(void)
{
	////サウンドの取得
	//CSound * pSound = CManager::GetSound();
	////もしサウンドのポインタがnullptrではない場合
	//if (pSound != nullptr)
	//{
	//	//キャンセル音の再生
	//	pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_CANCEL);
	//}
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CStageSelectButtonManager::InitCreateAll(void)
{
	//ステージ1ボタンの生成
	m_apButton[BUTTON_STAGE1] = CStage1Button::Create(D3DXVECTOR3(STAGE2_BUTTON_POSITION.x - 500.0f, STAGE2_BUTTON_POSITION.y, STAGE2_BUTTON_POSITION.z));
	//ステージ2ボタンの生成
	m_apButton[BUTTON_STAGE2] = CStage2Button::Create(STAGE2_BUTTON_POSITION);
	//ステージ3ボタンの生成
	m_apButton[BUTTON_STAGE3] = CStage3Button::Create(D3DXVECTOR3(STAGE2_BUTTON_POSITION.x + 500.0f, STAGE2_BUTTON_POSITION.y, STAGE2_BUTTON_POSITION.z));
}