//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 樋宮匠
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INIT_OFFSET			1000.0f	// 注視点からの距離
#define CAMERA_FIT_ANGLE D3DXToRadian(-90)
#define CAMERA_ROTATE_FRAME_LENGTH 90 // カメラを90度回転させるまでのフレーム数
#define CAMERA_ROTATE_ANGLE 90 // 一回の回転で回す角度

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInputKeyboard;

//================================================
// ライトクラス宣言
//================================================
class CCamera :public CObject
{
public:
	typedef enum
	{
		ROTATE_NONE = 0,
		ROTATE_LEFT,
		ROTATE_RIGHT,
	}ROTATE;

	typedef enum
	{
		ORIENTATION_NONE = -1,
		ORIENTATION_BACK,
		ORIENTATION_LEFT,
		ORIENTATION_FRONT,
		ORIENTATION_RIGHT,
		ORIENTATION_MAX,
	}ORIENTATION;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCamera(void);
	void RotateCamera(ROTATE dir);
	void OrientationControl(ROTATE dir);

	void SetTargetPos(D3DXVECTOR3 pos) { m_posR = pos; }	// 注視点設定
	void SetPos(D3DXVECTOR3 pos) { m_posV = pos; }			// 座標設定
	void SetFOV(float fFOV) { m_fFOV = fFOV; }				// 視野角設定
	void DecisionRotate(CInputKeyboard *pInputKeyboard);

	static CCamera *Create(void);

	ROTATE GetRotake(void) { return m_rotDir; }
	ROTATE GetRotakeOld(void) { return m_rotDirOld; }
	ORIENTATION GetOrientation(void) { return m_Orientation; }

	D3DXVECTOR3 GetTargtPos(void) { return m_posR; }		// 注視点取得
	D3DXVECTOR3 GetPos(void) { return m_posV; }				// 座標取得

private:
	D3DXVECTOR3 m_posV;
	D3DXVECTOR3 m_posR;
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_posVDest;								// 座標目標値
	D3DXVECTOR3 m_posRDest;
	D3DXVECTOR3 m_FollowPos;

	D3DXMATRIX  m_mtxProjection;
	D3DXMATRIX  m_mtxView;

	ROTATE      m_rotDir;
	ROTATE      m_rotDirOld;

	ORIENTATION m_Orientation;

	int			m_nRotateCountFrame;
	int         m_nOrientation;

	float		m_fFOV;
	float		m_fOffset;								// 注視点からの距離
	float		m_fVerticalAngle;						// 球面座標カメラ縦回転
	float		m_fHorizontalAngle;
};

#endif