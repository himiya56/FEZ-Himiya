//========================
// �C���N���[�h�t�@�C��
//========================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "collisiondetection.h"
#include "polygon2d.h"

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

CPlayer::CPlayer() {
	
}

CPlayer::~CPlayer() {

}

HRESULT CPlayer::Init(void) {
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CBillboard::Init();
	m_move = D3DXVECTOR3(MOVE_SIZ, 0, MOVE_SIZ);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Character1.1.png", &m_pTexture);
	BindTexture(m_pTexture);

	m_bJumpJudge = true;

	return S_OK;
}

void CPlayer::Uninit(void) {
	CBillboard::Uninit();
}

void CPlayer::Update(void) {
	m_pCamera = CManager::GetCamera();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	m_posold = m_pos;
	m_pos = GetPos();
	m_move.y -= GRAVITY_SIZ;

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
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x += m_move.x;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x -= m_move.x;
			}
			break;

		case CCamera::ORIENTATION_LEFT:
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z += m_move.z;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z -= m_move.z;
			}
			break;

		case CCamera::ORIENTATION_FRONT:
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x -= m_move.x;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x += m_move.x;
			}
			break;

		case CCamera::ORIENTATION_RIGHT:
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z -= m_move.z;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z += m_move.z;
			}
			break;
		}

		// �X�y�[�X�L�[�ŃW�����v
		if (m_bJumpJudge == true && pKeyboard->GetKeyboardTrigger(DIK_UP)) {
			m_bJumpJudge = false;
			m_move.y = JUMP_SIZ;
		}
	}

	m_pos.y += m_move.y;
	if (m_pos.y <= 0) {
		m_pos.y = 0;
		m_bJumpJudge = true;
	}

	CollisionDetection();

	SetCol(D3DXCOLOR(0, 0, 0, 255));
	SetPos(m_pos);
	CBillboard::Update();
}

void CPlayer::CollisionDetection(void) {
	// �u���b�N�Ƃ̓����蔻��
	CCollisionDetection *pCollisionDetection = CCollisionDetection::GetCollisionDetectionOrientation();

	for (int nCntScene = 0; nCntScene < CCollisionDetection::GetNumAll(); nCntScene++) {
		// ���g������Ȃ�
		if (pCollisionDetection != NULL) {
			// ���̃V�[�����L��
			CCollisionDetection *pNextScene = pCollisionDetection->GetNextScene();

			//Z��X������v�����ꍇ
			if (pCollisionDetection->GetPos().z == m_pos.z || pCollisionDetection->GetPos().x == m_pos.x){
				bool bCollisionDetectionJudge = CollisionDetectionCalculation(m_posold, m_pos, m_siz, pCollisionDetection->GetPos(), pCollisionDetection->GetSiz());

				if (bCollisionDetectionJudge == true) {
					m_pos.y = pCollisionDetection->GetPos().y + ((pCollisionDetection->GetSiz().y / 2) + (m_siz.y / 2));
				}
			}

			// ���̃V�[���ɂ���
			pCollisionDetection = pNextScene;
		}
		else {
			// ���g���Ȃ��Ȃ�A�����ŏ������I����
			break;
		}
	}
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
	pPlayer->m_pos = pos;
	pPlayer->m_siz = siz;
	return pPlayer;
}