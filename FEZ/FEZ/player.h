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
};

#endif