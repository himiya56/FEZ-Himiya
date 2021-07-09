//========================
// インクルードファイル
//========================
#include "collisiondetection.h"
#include "manager.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CCollisionDetection::m_nNum = 0;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListTop;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListCur;

CCollisionDetection::CCollisionDetection() {
	// 先頭がないなら、先頭に
	if (m_CollisionDetectionListTop == NULL)
	{
		m_CollisionDetectionListTop = this;
	}

	// 現在における最新のオブジェクトがないなら、最新に
	if (m_CollisionDetectionListCur == NULL)
	{
		m_CollisionDetectionListCur = this;
	}

	// 現在のオブジェクトの次のオブジェクトを、自分にする
	m_CollisionDetectionListCur->m_pNext = this;

	// 現在のオブジェクトが自分の場合
	if (m_CollisionDetectionListCur == this)
	{
		// 自分の前のオブジェクトを、NULLにする
		m_pPrev = NULL;
	}
	else
	{
		// 自分の前のオブジェクトを、現在のオブジェクトにする
		m_pPrev = m_CollisionDetectionListCur;
	}

	// 現在のオブジェクトを、自分にする
	m_CollisionDetectionListCur = this;

	// 自分の次のオブジェクトを、NULLにする
	m_pNext = NULL;

	// 使用するフラグをtrueに
	m_bUse = true;

	// 増えたオブジェクトをカウント
	m_nNum++;
}

CCollisionDetection::~CCollisionDetection() {

}

HRESULT CCollisionDetection::Init(void) {
	CPolygon2D::Init();

	return S_OK;
}

void CCollisionDetection::Uninit(void) {
	CPolygon2D::Uninit();
}

void CCollisionDetection::Update(void) {
	// 先頭、最新のものがあるなら
	if (m_CollisionDetectionListTop != NULL && m_CollisionDetectionListCur != NULL)
	{
		// 記憶用の変数
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionListTop;

		do
		{
			// 記憶用の変数(Update中に、Uninitされることを考慮)
			CCollisionDetection *pNextCollisionDetection = pCollisionDetection->m_pNext;

			// 使用フラグがfalseなら
			if (pCollisionDetection->m_bUse == false)
			{
				// メモリの開放
				//delete pScene;
				pCollisionDetection = NULL;
			}

			// 次のシーンに変えていく
			pCollisionDetection = pNextCollisionDetection;

		} while (pCollisionDetection != NULL);
	}
}

void CCollisionDetection::Draw(void) {
	CPolygon2D::Draw();
}

CCollisionDetection *CCollisionDetection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz) {
	CCollisionDetection* pCollisionDetection = NULL;
	pCollisionDetection = new CCollisionDetection;
	pCollisionDetection->Init();
	pCollisionDetection->SetPos(pos);
	pCollisionDetection->SetSize(siz.y, siz.x);
	pCollisionDetection->m_pos = pos;
	pCollisionDetection->m_siz = siz;
	return pCollisionDetection;
}

void CCollisionDetection::ReleaseAll(void)
{
	// 先頭、最新のものがあるなら
	if (m_CollisionDetectionListTop != NULL && m_CollisionDetectionListCur != NULL)
	{
		// 記憶用の変数
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionListCur;

		do
		{
			// 記憶用の変数
			CCollisionDetection *pNextpCollisionDetection = pCollisionDetection->m_pNext;

			// 終了処理
			pCollisionDetection->Uninit();

			// 使用フラグがfalseなら
			if (pCollisionDetection->m_bUse == false)
			{
				// メモリの開放
				//delete pScene;
				pCollisionDetection = NULL;
			}

			// 次のシーンに変えていく
			pCollisionDetection = pNextpCollisionDetection;

		} while (pCollisionDetection != NULL);
	}
}