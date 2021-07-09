//=============================================================================
//
// �I���{�^�� [button_exit.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
//#include "sound.h"
#include "button_exit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("data/TEXTURE/Button_Exit.png")		//�e�N�X�`���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExitButton::m_pTexture = NULL;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExitButton::CExitButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExitButton::~CExitButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExitButton::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	//�f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,					//�t�@�C���̖��O
		&m_pTexture);					//�ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CExitButton::TextureUnload(void)
{
	//�����e�N�X�`���̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CExitButton * CExitButton::Create(D3DXVECTOR3 Position)
{
	//�I���{�^���̃|�C���^
	CExitButton * pExitButton = NULL;
	//�I���{�^���̃|�C���^��NULL�̏ꍇ
	if (pExitButton == NULL)
	{
		//�I���{�^���̃������m��
		pExitButton = new CExitButton;
		//�I���{�^���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pExitButton != NULL)
		{
			//�I���{�^���̈ʒu�ݒ�
			pExitButton->SetPos(Position);
			//�I���{�^���̏����������֐��Ăяo��
			pExitButton->Init();
		}
	}
	//�I���{�^���̃|�C���^��Ԃ�
	return pExitButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CExitButton::Init(void)
{
	//�{�^���̏����������֐��Ăяo��
	CButton::Init();
	//�e�N�X�`���̐ݒ�
	SetTexUV(0.0f, 1.0f, 0.0f, 1.0f);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CExitButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CExitButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CExitButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CExitButton::Press(void)
{
	////�T�E���h�̎擾
	//CSound * pSound = CManager::GetSound();
	////�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	//if (pSound != NULL)
	//{
	//	//���艹�̍Đ�
	//	pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	//}
	////�I��������
	exit(0);
}