//=============================================================================
//
// ステージ3ボタン [button_stage3.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_STAGE3_H_
#define _BUTTON_STAGE3_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStage3Button :public CButton
{
public:
	CStage3Button();
	~CStage3Button();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CStage3Button * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif