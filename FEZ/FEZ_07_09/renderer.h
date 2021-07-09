//=============================================================================
//
// �`�揈�� [renderer.h]
// Author : ��{ ��
//
//=============================================================================

// ��d�C���N���[�h�h�~�p
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_POLYGON 1024

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CCamera;
class CPlayer;

//*****************************************************************************
// �����_���[�N���X��`
//*****************************************************************************
class CRenderer
{
public:
	// �����o�֐�
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	// �����o�֐�
	void DrawFPS(void);
	void DrawOrientation(void);
	void DrawPos(void);

	// �����o�ϐ�
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	        // Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^

	CCamera *m_pCamera;
	CPlayer *m_pPlayer;
};

#endif
