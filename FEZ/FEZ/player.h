//====================================================================
//
// �r���{�[�h���� (billboard.h)
// Author : �����N�m
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "billboard.h"

//================================================
// �N���X�錾
//================================================

// �r���{�[�h�N���X
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