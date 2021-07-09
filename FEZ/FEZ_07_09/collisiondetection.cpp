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
CCollisionDetection *CCollisionDetection::m_CollisionDetectionOrientationTop;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionOrientationCur;

CCollisionDetection::CCollisionDetection() {
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
	m_pCamera = CManager::GetCamera();

	// 先頭、最新のものがあるなら
	if (m_CollisionDetectionListTop != NULL && m_CollisionDetectionListCur != NULL)
	{
		// 記憶用の変数
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionListTop;

		do
		{
			// 記憶用の変数(Update中に、Uninitされることを考慮)
			CCollisionDetection *pNextCollisionDetection = pCollisionDetection->m_pNext;

			if (m_pCamera->GetOrientation() != CCamera::ROTATE_NONE) {
				ReleaseAll();
			}

			if (pCollisionDetection->m_Orientation == m_pCamera->GetOrientation()) {
				SetCollisionDetectionOrientation(pCollisionDetection->m_pos, pCollisionDetection->m_siz);
			}

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

CCollisionDetection *CCollisionDetection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, CCamera::ORIENTATION Orientation) {
	CCollisionDetection *pCollisionDetection = NULL;
	pCollisionDetection = new CCollisionDetection;
	pCollisionDetection->Init();
	pCollisionDetection->SetPos(pos);
	pCollisionDetection->SetSize(siz.y, siz.x);
	pCollisionDetection->SetCollisionDetectionList(pos, siz, Orientation);
	return pCollisionDetection;
}

void CCollisionDetection::SetCollisionDetectionList(D3DXVECTOR3 pos, D3DXVECTOR3 siz, CCamera::ORIENTATION Orientation) {
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

	// 方向をNONEにする
	m_Orientation = Orientation;

	// 使用するフラグをtrueに
	m_bUse = true;
}

void CCollisionDetection::SetCollisionDetectionOrientation(D3DXVECTOR3 pos, D3DXVECTOR3 siz) {
	// 先頭がないなら、先頭に
	if (m_CollisionDetectionOrientationTop == NULL)
	{
		m_CollisionDetectionOrientationTop = this;
	}

	// 現在における最新のオブジェクトがないなら、最新に
	if (m_CollisionDetectionOrientationCur == NULL)
	{
		m_CollisionDetectionOrientationCur = this;
	}

	// 現在のオブジェクトの次のオブジェクトを、自分にする
	m_CollisionDetectionOrientationCur->m_pNext = this;

	// 現在のオブジェクトが自分の場合
	if (m_CollisionDetectionOrientationCur == this)
	{
		// 自分の前のオブジェクトを、NULLにする
		m_pPrev = NULL;
	}
	else
	{
		// 自分の前のオブジェクトを、現在のオブジェクトにする
		m_pPrev = m_CollisionDetectionOrientationCur;
	}

	// 現在のオブジェクトを、自分にする
	m_CollisionDetectionOrientationCur = this;

	// 自分の次のオブジェクトを、NULLにする
	m_pNext = NULL;

	// 使用するフラグをtrueに
	m_bUse = true;
}

void CCollisionDetection::ReleaseAll(void)
{
	// 先頭、最新のものがあるなら
	if (m_CollisionDetectionOrientationTop != NULL && m_CollisionDetectionOrientationCur != NULL)
	{
		// 記憶用の変数
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionOrientationTop;

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