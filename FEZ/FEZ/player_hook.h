//====================================================================
//
// プレイヤー12処理 (player_hook.h)
// Author : 樋宮 匠
//
//====================================================================
#ifndef _PLAYER_HOOK_H_
#define _PLAYER_HOOK_H_

//================================================
// インクルードファイル
//================================================
#include "player.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEST_HOOK_POS D3DXVECTOR3(300.0f, 300.0f, 0.0f)
#define HOOK_SPD_RATE 5.0f
#define HOOK_STOP_SIZE 5.0f

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CPlayerHook : public CPlayer
{
public:
	CPlayerHook();
	~CPlayerHook();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ShotHook(D3DXVECTOR3 pos);
	void MoveToHook(D3DXVECTOR3 pos);


	static CPlayerHook *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);
	static void Load(void);
	static void Unload(void);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	bool m_bHook;

	static LPDIRECT3DTEXTURE9		m_pTexture;
};

#endif