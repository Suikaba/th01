#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3dx9.h>
#include <string>
using namespace std;


class CGraphics {
private:

	LPDIRECT3D9 lpD3D;
	LPDIRECT3DDEVICE9 lpd3dDev;
	LPD3DXSPRITE lpSprite;

	// �E�B���h�E�n���h��
	HWND hWnd, DesktophWnd;

	// ���̃E�B���h�E�X�^�C��
	DWORD WindowStyle;

	// ���A����
	int Width, Height;

public:

	// �R���X�g���N�^
	CGraphics( HWND hwnd );
	~CGraphics();

	// �e����
	LPDIRECT3DDEVICE9 GetDevice() { return lpd3dDev; }
	LPD3DXSPRITE GetSprite() { return lpSprite; }
	HWND GetWindowHandle() { return hWnd; }
	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	// �e����̐ݒ�
	void SetWidth( int w ) { Width = w; }
	void SetHeight( int h ) { Height = h; }

	// �f�o�C�X�̃��Z�b�g
	bool ResetDevice();

	// �`��̐ݒ�
	void InitDraw();

	// ��ʏ����A�v���b�v
	void Clear( D3DCOLOR color = D3DCOLOR_ARGB( 255, 0, 0, 0 ) );
	bool Present();

	// �V�[���`��̊J�n�A�I��
	void BeginScene() { lpd3dDev->BeginScene(); }
	void EndScene() { lpd3dDev->EndScene(); }

	// �X�v���C�g�`��̊J�n�A�I��
	void BeginSprite() { lpSprite->Begin( NULL ); }
	void EndSprite() { lpSprite->End(); }

	// �X�v���C�g�`��
	void SpriteDraw( float x, float y, LPDIRECT3DTEXTURE9 texture );

	// �e�N�X�`���̓ǂݍ���
	LPDIRECT3DTEXTURE9 LoadTexture( string file );
	LPDIRECT3DTEXTURE9 LoadTexture( string file, int r, int g, int b );
};

#endif