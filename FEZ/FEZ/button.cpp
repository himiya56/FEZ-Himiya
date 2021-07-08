//=============================================================================
//
// ボタン [button.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
//#include "sound.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SELECT_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))		//選択時の色
#define NOT_SELECT_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,0.5f))	//選択されていないときの色
#define SIZE (D3DXVECTOR3(200.0f,700.0f,0.0f))				//サイズ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CButton::CButton(OBJ_TYPE nObjectType) : CPolygon2D(nObjectType)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CButton::~CButton()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CButton::Init(void)
{
	//シーン2D管理の初期化処理関数呼び出し
	CPolygon2D::Init();
	//サイズを設定する
	SetSize(SIZE.y, SIZE.x);
	//色を設定する
	SetCol(NOT_SELECT_COLOR);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CButton::Uninit(void)
{
	//シーン2D管理の終了処理関数呼び出し
	CPolygon2D::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CButton::Update(void)
{
	//シーン2D管理の更新処理関数呼び出し
	CPolygon2D::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CButton::Draw(void)
{
	//シーン2D管理の描画処理関数呼び出し
	CPolygon2D::Draw();
}

//=============================================================================
// 選択していない時の色変更処理関数
//=============================================================================
void CButton::NotSelectColor(void)
{
	//色を変更する
	SetCol(NOT_SELECT_COLOR);
}

//=============================================================================
// 選択時色変更処理関数
//=============================================================================
void CButton::SelectColor(void)
{
	//色を変更する
	SetCol(SELECT_COLOR);
}

//=============================================================================
// 選択時音再生処理関数
//=============================================================================
void CButton::SelectSound(void)
{
	////サウンドの取得
	//CSound * pSound = CManager::GetSound();
	////もしサウンドのポインタがnullptrではない場合
	//if (pSound != nullptr)
	//{
	//	//選択音の再生
	//	pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_SELECT);
	//}
}
