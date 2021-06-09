//========================
// インクルードファイル
//========================
#include "player.h"
#include "manager.h"
#include "keyboard.h"

CPlayer::CPlayer() {
	m_pCamera = new CCamera;
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
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	m_pos = GetPos();

	if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
		if (Orientation == CCamera::ORIENTATION_FRONT || Orientation == CCamera::ORIENTATION_BACK) {
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x -= MOVE_SIZ;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x += MOVE_SIZ;
			}
		}
		if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT) {
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z -= MOVE_SIZ;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z += MOVE_SIZ;
			}
		}

		// スペースキーでジャンプ
		if (pKeyboard->GetKeyboardTrigger(DIK_UP)) {
			m_pos.y += MOVE_SIZ;
		}
	}

	SetPos(m_pos);
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