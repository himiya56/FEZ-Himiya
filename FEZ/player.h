//====================================================================
//
// ビルボード処理 (billboard.h)
// Author : 東村哲士
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "billboard.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_SIZ 10.0f
#define JUMP_SIZ 10.0f
#define GRAVITY_SIZ 0.27f

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CPlayer : public CBillboard
{
public:
	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CollisionDetection(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_siz;
	D3DXVECTOR3 m_move;
	bool m_bJumpJudge;

	static LPDIRECT3DTEXTURE9		m_pTexture;

	CCamera *m_pCamera;
};

#endif