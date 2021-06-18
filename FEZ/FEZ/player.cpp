//========================
// インクルードファイル
//========================
#include "player.h"
#include "manager.h"
#include "keyboard.h"

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

CPlayer::CPlayer() {
	
}

CPlayer::~CPlayer() {

}

HRESULT CPlayer::Init(void) {
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CBillboard::Init();
	m_move = MOVE_SIZ;
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Character1.png", &m_pTexture);
	BindTexture(m_pTexture);

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

	//if (Orientation == CCamera::ORIENTATION_FRONT) {
	//	m_pos.z = -20;
	//}
	//if (Orientation == CCamera::ORIENTATION_BACK) {
	//	m_pos.z = 20;
	//}
	//if (Orientation == CCamera::ORIENTATION_LEFT) {
	//	m_pos.x = -100;
	//}
	//if (Orientation == CCamera::ORIENTATION_RIGHT) {
	//	m_pos.x = 5;
	//}

	if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
		switch (Orientation) {
		case CCamera::ORIENTATION_BACK:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x += m_move;
				SetTexUVX(1.0f,0.0f);
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x -= m_move;
				SetTexUVX(0.0f, 1.0f);
			}
			break;

		case CCamera::ORIENTATION_LEFT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z += m_move;
				SetTexUVX(1.0f, 0.0f);
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z -= m_move;
				SetTexUVX(0.0f, 1.0f);
			}
			break;

		case CCamera::ORIENTATION_FRONT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x -= m_move;
				SetTexUVX(1.0f, 0.0f);
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x += m_move;
				SetTexUVX(0.0f, 1.0f);
			}
			break;

		case CCamera::ORIENTATION_RIGHT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z -= m_move;
				SetTexUVX(1.0f, 0.0f);
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z += m_move;
				SetTexUVX(0.0f, 1.0f);
			}
			break;
		}

		// スペースキーでジャンプ
		if (pKeyboard->GetKeyboardTrigger(DIK_UP)) {
			m_pos.y += MOVE_SIZ;
		}
	}

	CollisionDetection();

	SetCol(D3DXCOLOR(0, 0, 0, 255));
	SetPos(m_pos);
	CBillboard::Update();
}

void CPlayer::CollisionDetection(void) {

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