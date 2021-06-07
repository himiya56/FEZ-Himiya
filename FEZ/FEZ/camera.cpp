//===============================================
//
// �J�������� (camera.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixIdentity(&m_mtxProjection);

	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_posVDest = DEFAULT_VECTOR;
	m_posRDest = DEFAULT_VECTOR;
	m_fVerticalAngle = D3DXToRadian(270);
	m_fHorizontalAngle = D3DXToRadian(90);
	m_fOffset = INIT_OFFSET;
	m_fFOV = 90.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fFOV = 90.0f;

	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(m_fFOV), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 2000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *pKeyboard = CManager::GetInput();

	// A�L�[�ō���]
	if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		m_fVerticalAngle -= D3DXToRadian(1.0f);
		// 0�x�ȉ��ɂȂ�Ȃ��悤��
		if (m_fVerticalAngle <= 0.0f)
		{
			m_fVerticalAngle = D3DXToRadian(360.0f);
		}
	}
	// D�L�[�ŉE��]
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		m_fVerticalAngle += D3DXToRadian(1.0f);
		// 360�x�ȏ�ɂȂ�Ȃ��悤��
		if (m_fVerticalAngle >= D3DXToRadian(360.0f))
		{
			m_fVerticalAngle = D3DXToRadian(0.0f);
		}
	}

	// �ړI�n�̌v�Z(���ʍ��W)
	m_posRDest.x = m_fOffset * (sinf(m_fHorizontalAngle) * cosf(m_fVerticalAngle));
	m_posRDest.y = m_fOffset * cosf(m_fHorizontalAngle);
	m_posRDest.z = m_fOffset * (sinf(m_fHorizontalAngle) * sinf(m_fVerticalAngle));

	// �ړI�n�ɋ߂Â���
	m_posR += (m_posRDest - m_posR) * 0.9f;
	m_posV += (m_posVDest - m_posV) * 0.9f;

	// ���W�X�V
	SetTargetPos(m_posR);
	SetPos(m_posV);

	// �J�����A�b�v�f�[�g
	SetCamera();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCamera::Draw(void)
{
}

//=============================================================================
// �J�����X�V����(�������e)
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(m_fFOV), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	D3DXMatrixOrthoLH(&m_mtxProjection, SCREEN_WIDTH, SCREEN_HEIGHT, 10.0f, 10000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// �J��������
//=============================================================================
CCamera * CCamera::Create(void)
{
	CCamera *pCamera;
	pCamera = new CCamera;
	pCamera->Init();
	return pCamera;
}
