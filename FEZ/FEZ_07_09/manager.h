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
class CSound;
class CGameMode;
class CFade;

//*****************************************************************************
// マネージャークラス定義
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_STAGE_SELECT,
		MODE_GAME_STAGE1,
		MODE_GAME_STAGE2,
		MODE_GAME_STAGE3,
		MODE_MAX
	}MODE;
	// メンバ関数
	CManager();													 // コンストラクタ
	~CManager();												 // デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);  // 初期化処理
	void Uninit(void);											 // 終了処理
	void Update(void);											 // 更新処理
	void Draw(void);											 // 描画処理
	void Load(void);											 // モデル・テクスチャ読み込み
	void Unload(void);											 // モデル・テクスチャ破棄
	static void StartFade(MODE mode);
	static void StopFade(void);
	static void SetMode(MODE Mode);
	static MODE GetMode(void) { return m_Mode; }
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInput(void) { return m_pInput; }
	static CCamera *GetCamera(void) { return m_pCamera; }

	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CSound *GetSound(void) { return m_pSound; }
	static CGameMode *GetGameMode(void) { return m_pGameMode; }
	static CFade * GetFade(void) { return m_pFade; }
private:
	// メンバ変数
	static MODE				 m_Mode;					  //モード
	static bool				 m_bUseFade;				  //フェードの使用状態

	static CRenderer		*m_pRenderer;
	static CSound           *m_pSound;
	static CInputKeyboard   *m_pInput;
	static CCamera			*m_pCamera;

	static CLight			*m_pLight;		                     // ライトのポインタ
	static CPlayer          *m_pPlayer;
	static CCollisionDetection *m_CollisionDetection;

	static CGameMode		*m_pGameMode;				  // ゲームモードのポインタ
	static CFade			*m_pFade;					  //フェードのポインタ

};

#endif