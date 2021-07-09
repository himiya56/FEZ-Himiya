//=============================================================================
//
// ポリゴン処理 [object.h]
// Author : 樋宮 匠
//
//=============================================================================

// 二重インクルード防止用
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"

//*****************************************************************************
// オブジェクトクラス定義
//*****************************************************************************
class CObject
{
public:
	// 列挙型宣言
	typedef enum
	{
		OBJ_TYPE_NONE = 0,
		OBJ_TYPE_HOOK,
		OBJ_TYPE_BUTTON,
		OBJ_TYPE_MAX
	}OBJ_TYPE;

	// メンバ関数
	CObject();
	CObject(OBJ_TYPE objType);
	virtual ~CObject();
	// 純粋仮想関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static  void UpdateAll(void);
	static  void DrawAll(void);
	static  void ReleaseAll(void);	// 全オブジェクト破棄関数

	static  int GetNumObj(OBJ_TYPE objType) {return m_nNumObj[objType]; }
	static  CObject*GetTopObj(OBJ_TYPE objType) { return m_pTop[objType]; }
	CObject* GetNextObj(void) { return m_pNext; }
protected:
	void Release(void);		// オブジェクト破棄関数
private:
	static CObject *m_pTop[OBJ_TYPE_MAX];
	static CObject *m_pCur[OBJ_TYPE_MAX];
	CObject *m_pPrev;
	CObject *m_pNext;

	static int m_nNumAll;
	static int m_nNumObj[OBJ_TYPE_MAX];
	OBJ_TYPE	m_type;

	bool m_bUse;
};

#endif

