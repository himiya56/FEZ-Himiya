//========================
// インクルードファイル
//========================
#include "player.h"
#include "manager.h"
#include "keyboard.h"

CPlayer::CPlayer() {
	
}

CPlayer::~CPlayer() {

}

HRESULT CPlayer::Init(void) {
	CBillboard::Init();
	m_move = MOVE_SIZ;

	return S_OK;
}

void CPlayer::Uninit(void) {
	CBillboard::Uninit();
}

void CPlayer::Update(void) {
	m_pCamera = CManager::GetCamera();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	m_pos = GetPos();

	if (Orientation == CCamera::ORIENTATION_FRONT && Orientation == CCamera::ORIENTATION_BACK) {
		m_pos.z = 0;
	}
	if (Orientation == CCamera::ORIENTATION_LEFT && Orientation == CCamera::ORIENTATION_RIGHT) {
		m_pos.x = 0;
	}

	if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
		switch (Orientation) {
		case CCamera::ORIENTATION_FRONT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x -= m_move;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x += m_move;
			}
			break;

		case CCamera::ORIENTATION_BACK:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x += m_move;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x -= m_move;
			}
			break;

		case CCamera::ORIENTATION_LEFT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z += m_move;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z -= m_move;
			}
			break;

		case CCamera::ORIENTATION_RIGHT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z -= m_move;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z += m_move;
			}
			break;
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