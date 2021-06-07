#pragma once
//====================================================================
//
// テストオブジェクトの処理 (testObj.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _TESTOBJ_H_
#define _TESTOBJ_H_

//================================================
// インクルードファイル
//================================================
#include "scene3d.h"

//================================================
// マクロ定義
//================================================

//================================================
// クラス宣言
//================================================

// UIクラス
class CTestObj : public CScene3D
{
public:
	CTestObj();
	~CTestObj();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CTestObj *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
};

#endif