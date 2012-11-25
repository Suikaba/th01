#include "Graphics.h"


//==================================================================
// �R���X�g���N�^
CGraphics::CGraphics( HWND hwnd )
:	hWnd( hwnd ), lpD3D( NULL ), lpd3dDev( NULL ), lpSprite( NULL )
{
	// �E�B���h�E�X�^�C���̕ۑ�
	WindowStyle = GetWindowLong( hwnd, GWL_STYLE );

	// �N���C�A���g�̈�̃T�C�Y���擾
	RECT r;
	GetClientRect( hwnd, &r );
	Width = r.right - r.left;
	Height = r.bottom - r.top;

	// Direct3D�C���^�[�t�F�C�X�̍쐬
	lpD3D = Direct3DCreate9( D3D_SDK_VERSION );

	// Direct3D�f�o�C�X�̍쐬
	ResetDevice();

	D3DXCreateSprite( lpd3dDev, &lpSprite );
}


//==================================================================
// �f�X�g���N�^
CGraphics::~CGraphics() {
	if( lpSprite != NULL )
		lpSprite->Release();
	if( lpd3dDev != NULL )
		lpd3dDev->Release();
	if( lpD3D != NULL )
		lpD3D->Release();
}


//==================================================================
// �f�o�C�X�̃��Z�b�g
bool CGraphics::ResetDevice() {

	// �E�B���h�E�X�^�C���ƃT�C�Y�̐ݒ�
	RECT wr;
	DesktophWnd = GetDesktopWindow();
	GetWindowRect( DesktophWnd, &wr );
	SetWindowLong( hWnd, GWL_STYLE, WindowStyle );
	RECT r;
	GetWindowRect( hWnd, &r );
	/*RECT r = { 0, 0, Width, Height };
	AdjustWindowRect( &r, WindowStyle, false ); */
	SetWindowPos( hWnd, HWND_NOTOPMOST,
		( wr.right-( r.right-r.left ) )/2, ( wr.bottom-( r.bottom-r.top ) )/2,
		r.right-r.left, r.bottom-r.top, SWP_SHOWWINDOW );

	

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if( !lpd3dDev ) {

		if( FAILED( lpD3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp, &lpd3dDev ) )
		)
		if( FAILED( lpD3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &lpd3dDev ) )
		)
		if( FAILED( lpD3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &lpd3dDev ) )
		) return false;
	} else {
		if( FAILED( lpd3dDev->Reset( &d3dpp ) ) ) return false;
	}

	// ���ƍ����̎擾
	LPDIRECT3DSURFACE9 back_buffer;
	if( SUCCEEDED( lpd3dDev->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer ) ) ) {
		D3DSURFACE_DESC desc;
		back_buffer->GetDesc( &desc );
		Width = desc.Width;
		Height = desc.Height;
		back_buffer->Release();
	} else {
		Width = Height = 0;
	}

	InitDraw();

	return true;
}


//==================================================================
// �`��̐ݒ�
void CGraphics::InitDraw() {
	lpd3dDev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	lpd3dDev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}


//==================================================================
// ��ʂ̏���
void CGraphics::Clear( D3DCOLOR color ) {
	lpd3dDev->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		color, 1.0f, 0 );
}


//==================================================================
// �t���b�v
bool CGraphics::Present() {
	if( FAILED( lpd3dDev->Present( NULL, NULL, NULL, NULL ) ) )
		return false;

	return true;
}


//==================================================================
// �X�v���C�g�`��
void CGraphics::SpriteDraw( float x, float y, LPDIRECT3DTEXTURE9 texture ) {
	D3DXVECTOR3 center, position;
	position.x = x;
	position.y = y;
	center.x = 0;
	center.y = 0;
	lpSprite->Draw( texture, NULL, &center, &position, 0xffffffff );
}


//==================================================================
// �e�N�X�`���̓ǂݍ���
LPDIRECT3DTEXTURE9 CGraphics::LoadTexture( string file ) {
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile( file.c_str(), &info );
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXCreateTextureFromFileEx( lpd3dDev, file.c_str(),
		info.Width, info.Height, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, 
		0, NULL, NULL, &texture );
	return texture;
}

LPDIRECT3DTEXTURE9 CGraphics::LoadTexture( string file, int r, int g, int b ) {
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile( file.c_str(), &info );
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXCreateTextureFromFileEx( lpd3dDev, file.c_str(),
		info.Width, info.Height, 0, 0, D3DFMT_A1R5G5B5, D3DPOOL_MANAGED, 
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, 
		D3DCOLOR_ARGB( 255, r, g, b ), NULL, NULL, &texture );
	return texture;
}