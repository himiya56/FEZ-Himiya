//====================================================================
//
// ポリゴン(当たり判定用)処理 (block.h)
// Author : 東村哲士
//
//====================================================================
#ifndef _COLLISIONDETECTION_H_
#define _COLLISIONDETECTION_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "polygon2d.h"
#include "camera.h"

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CCollisionDetection : public CPolygon2D
{
public:
	CCollisionDetection();
	~CCollisionDetection();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReleaseAll(void);

	void SetCollisionDetectionList(D3DXVECTOR3 pos, D3DXVECTOR3 siz, CCamera::ORIENTATION Orientation);
	void SetCollisionDetectionOrientation(D3DXVECTOR3 pos, D3DXVECTOR3 siz);

	static CCollisionDetection *GetCollisionDetectionOrientation(void) { return m_CollisionDetectionOrientationTop; }

	static CCollisionDetection *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, CCamera::ORIENTATION Orientation);

private:
	static int m_nNum;

	CCamera::ORIENTATION m_Orientation;

	static CCollisionDetection *m_CollisionDetectionListTop;
	static CCollisionDetection *m_CollisionDetectionListCur;
	static CCollisionDetection *m_CollisionDetectionOrientationTop;
	static CCollisionDetection *m_CollisionDetectionOrientationCur;
	CCollisionDetection *m_pPrev;
	CCollisionDetection *m_pNext;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_siz;

	bool m_bUse;

	CCamera *m_pCamera;
};

#endif