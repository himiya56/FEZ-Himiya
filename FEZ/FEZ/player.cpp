//========================
// インクルードファイル
//========================
#include "player.h"
#include "manager.h"

CPlayer::CPlayer() {

}

CPlayer::~CPlayer() {

}

HRESULT CPlayer::Init(void) {
	CBillboard::Init();

	return S_OK;
}

void CPlayer::Uninit(void) {
	CBillboard::Uninit();
}

void CPlayer::Update(void) {
	CBillboard::Update();
}

void CPlayer::Draw(void) {
	CBillboard::Draw();
}

CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz) {
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetSize(siz);
	return pPlayer;
}