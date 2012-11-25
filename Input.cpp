#include "Input.h"



//==============================================================
// コンストラクタ
CInput::CInput( HWND hWnd ) 
:	lpDI( NULL ), lpDIDevice( NULL ), Left( false ), Right( false )
{

	if( FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&lpDI, NULL ) ) )
	{
		MessageBox( NULL, _T("まただめだったよ"), _T("失敗"), MB_OK );
		return;
	}

	lpDI->CreateDevice( GUID_SysKeyboard, &lpDIDevice, NULL );
	lpDIDevice->SetDataFormat( &c_dfDIKeyboard );
	lpDIDevice->SetCooperativeLevel( hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
}


//==============================================================
// デストラクタ
CInput::~CInput() {
	if( lpDIDevice != NULL ) {
		lpDIDevice->Unacquire();
		lpDIDevice->Release();
	}
	if( lpDI != NULL )
		lpDI->Release();
}


//==============================================================
// キー入力の状態を取得
void CInput::UpdataState() {
	if( !FAILED( lpDIDevice->Acquire() ) &&
		!FAILED( lpDIDevice->GetDeviceState(
			sizeof( m_keys ), &m_keys ) )
	) {
		Left |= ( ( m_keys[ DIK_LEFT ]&0x80 ) != 0 );
		Right |= ( ( m_keys[ DIK_RIGHT ]&0x80 ) != 0 );
		Z |= ( ( m_keys[ DIK_Z ]&0x80 ) != 0 );
		
	}
	
}


//==============================================================
// 何も押されていないようにする
void CInput::Clear() {
	Left = Right = Z = false;
}