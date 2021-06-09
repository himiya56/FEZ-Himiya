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
#define MOVE_SIZ 5.0f // キーの最大数

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

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);

private:
	D3DXVECTOR3 m_pos;

	CCamera *m_pCamera;
};

#endif