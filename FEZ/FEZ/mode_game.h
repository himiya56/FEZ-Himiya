//=============================================================================
//
// ゲームモード [mode_game.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameMode : CObject
{
public:
	typedef enum
	{
		STAGE_1 = 1,
		STAGE_2,
		STAGE_3,
		STAGE_MAX
	}STAGE;
	CGameMode();
	~CGameMode();
	static CGameMode * Create(STAGE Stage);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetbCreatePause(bool bPouse) { m_bCreatePause = bPouse; }
	bool GetbCreatePause(void) { return m_bCreatePause; }
private:
	void InitCreate(void);
	void InitStageCreate(void);
	void Input(void);
	bool m_bCreatePause;	//ポーズを生成してるか
	STAGE m_Stage;			//ステージ
};
#endif
