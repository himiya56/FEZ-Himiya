//=============================================================================
//
// マネージャー [manager.h]
// Author : 樋宮 匠
//
//=============================================================================

// 二重インクルード防止用
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CPlayer;
class CCollisionDetection;

//*****************************************************************************
// マネージャークラス定義
//*****************************************************************************
class CManager
{
public:
	// メンバ関数
	CManager();													 // コンストラクタ
	~CManager();												 // デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);  // 初期化処理
	void Uninit(void);											 // 終了処理
	void Update(void);											 // 更新処理
	void Draw(void);											 // 描画処理
	void Load(void);											 // モデル・テクスチャ読み込み
	void Unload(void);											 // モデル・テクスチャ破棄

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInput(void) { return m_pInput; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CCollisionDetection *GetCollisionDetection(void) { return m_CollisionDetection; }
private:
	// メンバ変数
	static CRenderer		*m_pRenderer;
	static CInputKeyboard   *m_pInput;
	static CCamera			*m_pCamera;
	static CLight			*m_pLight;		                     // ライトのポインタ
	static CPlayer          *m_pPlayer;
	static CCollisionDetection *m_CollisionDetection;
};

#endif