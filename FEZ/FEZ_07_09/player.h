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
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_SIZ 5.0f // プレイヤーの移動量
#define PLAYER_SIZE D3DXVECTOR3(150.0f, 150.0f, 0.0f)

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
	float m_move;

	static LPDIRECT3DTEXTURE9		m_pTexture;

	CCamera *m_pCamera;
};

#endif