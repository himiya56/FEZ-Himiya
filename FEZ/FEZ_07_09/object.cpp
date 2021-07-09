//=============================================================================
//
// ポリゴン処理 [object.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CObject::m_nNumAll = 0;
int CObject::m_nNumObj[CObject::OBJ_TYPE_MAX] = {};

CObject *CObject::m_pTop[CObject::OBJ_TYPE_MAX] = {};
CObject *CObject::m_pCur[CObject::OBJ_TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject()
{
	// オブジェクトの種類を指定がないのでNONEにする
	m_type = OBJ_TYPE_NONE;

	// 先頭がないなら、先頭に
	if (m_pTop[m_type] == NULL)
	{
		m_pTop[m_type] = this;
	}

	// 現在における最新のオブジェクトがないなら、最新に
	if (m_pCur[m_type] == NULL)
	{
		m_pCur[m_type] = this;
	}

	// 現在のオブジェクトの次のオブジェクトを、自分にする
	m_pCur[m_type]->m_pNext = this;

	// 現在のオブジェクトが自分の場合
	if (m_pCur[m_type] == this)
	{
		// 自分の前のオブジェクトを、NULLにする
		m_pPrev = NULL;
	}
	else
	{
		// 自分の前のオブジェクトを、現在のオブジェクトにする
		m_pPrev = m_pCur[m_type];
	}

	// 現在のオブジェクトを、自分にする
	m_pCur[m_type] = this;

	// 自分の次のオブジェクトを、NULLにする
	m_pNext = NULL;

	// 増えたオブジェクトをカウント
	m_nNumObj[m_type]++;

	// 全体の数をインクリメント
	m_nNumAll++;

	// 使用するフラグをtrueに
	m_bUse = true;
}

//=============================================================================
// オーバーライドされたコンストラクタ
//=============================================================================
CObject::CObject(OBJ_TYPE objType)
{
	// オブジェクトの種類を指定
	m_type = objType;

	// 先頭がないなら、先頭に
	if (m_pTop[m_type] == NULL)
	{
		m_pTop[m_type] = this;
	}

	// 現在における最新のオブジェクトがないなら、最新に
	if (m_pCur[m_type] == NULL)
	{
		m_pCur[m_type] = this;
	}

	// 現在のオブジェクトの次のオブジェクトを、自分にする
	m_pCur[m_type]->m_pNext = this;

	// 現在のオブジェクトが自分の場合
	if (m_pCur[m_type] == this)
	{
		// 自分の前のオブジェクトを、NULLにする
		m_pPrev = NULL;
	}
	else
	{
		// 自分の前のオブジェクトを、現在のオブジェクトにする
		m_pPrev = m_pCur[m_type];
	}

	// 現在のオブジェクトを、自分にする
	m_pCur[m_type] = this;

	// 自分の次のオブジェクトを、NULLにする
	m_pNext = NULL;

	// 増えたオブジェクトをカウント
	m_nNumObj[m_type]++;

	// 全体の数をインクリメント
	m_nNumAll++;

	// 使用するフラグをtrueに
	m_bUse = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// 全更新処理
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < OBJ_TYPE_MAX; nCnt++)
	{
		// 先頭、最新のものがあるなら
		if (m_pTop[nCnt] != NULL && m_pCur[nCnt] != NULL)
		{
			// 記憶用の変数
			CObject*pObj = m_pTop[nCnt];

			do
			{
				// 記憶用の変数(Update中に、Uninitされることを考慮)
				CObject*pNextScene = pObj->m_pNext;

				// 更新処理
				pObj->Update();

				// 使用フラグがfalseなら
				if (pObj->m_bUse == false)
				{
					// メモリの開放
					delete pObj;
					pObj = NULL;
				}

				// 次のシーンに変えていく
				pObj = pNextScene;

			} while (pObj != NULL);
		}
	}
}

//=============================================================================
// 全描画処理
//=============================================================================
void CObject::DrawAll(void)
{
	for (int nCnt = 0; nCnt < OBJ_TYPE_MAX; nCnt++)
	{
		// 先頭、最新のものがあるなら
		if (m_pTop[nCnt] != NULL && m_pCur[nCnt] != NULL)
		{
			// 記憶用の変数
			CObject*pObj = m_pTop[nCnt];

			do
			{
				// 描画処理
				pObj->Draw();

				// 次のシーンに変えていく
				pObj = pObj->m_pNext;

			} while (pObj != NULL);
		}
	}

	// デバッグ用
	int nDebug = m_nNumAll;
	nDebug = nDebug;
}

//=============================================================================
// 全オブジェクト破棄処理
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < OBJ_TYPE_MAX; nCnt++)
	{
		// 先頭、最新のものがあるなら
		if (m_pTop[nCnt] != NULL && m_pCur[nCnt] != NULL)
		{
			// 記憶用の変数
			CObject*pObj = m_pTop[nCnt];

			do
			{
				// 記憶用の変数
				CObject*pNextScene = pObj->m_pNext;

				// 終了処理
				pObj->Uninit();

				// 使用フラグがfalseなら
				if (pObj->m_bUse == false)
				{
					// メモリの開放
					delete pObj;
					pObj = NULL;
				}

				// 次のシーンに変えていく
				pObj = pNextScene;

			} while (pObj != NULL);
		}
	}
}

//=============================================================================
// オブジェクト破棄処理
//=============================================================================
void CObject::Release(void)
{
	// 中身があるなら、
	if (this != NULL)
	{
		// 先頭なら
		if (this == m_pTop[m_type])
		{
			// 次の中身があるなら
			if (m_pNext != NULL)
			{
				// 次のものの前の情報を、NULLに
				m_pNext->m_pPrev = NULL;

				// それを先頭に
				m_pTop[m_type] = m_pNext;
			}
			else
			{
				// 先頭の次がないなら、先頭と現在を示すポインタをNULLに
				m_pTop[m_type] = NULL;
				m_pCur[m_type] = NULL;
			}
		}
		// 先頭でないなら
		else
		{
			// 次の中身があるなら
			if (m_pNext != NULL)
			{
				// 前のものの次の情報を、自身の次の情報に
				m_pPrev->m_pNext = m_pNext;

				// 次のものの前の情報を、自身の前の情報に
				m_pNext->m_pPrev = m_pPrev;
			}
			else
			{
				// 前のものの次の情報を、なくす
				m_pPrev->m_pNext = NULL;

				// 現在の最新のものを、前の情報に
				m_pCur[m_type] = m_pPrev;
			}
		}

		// 使用フラグをfalseに
		m_bUse = false;

		// 種類ごとの総数を減らす
		m_nNumObj[m_type]--;

		// 全体の数をデクリメント
		m_nNumAll--;
	}
}