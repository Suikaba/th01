#ifndef INPUT_H
#define INPUT_H

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <tchar.h>

class CInput {
private:

	LPDIRECTINPUT8 lpDI;
	LPDIRECTINPUTDEVICE8 lpDIDevice;

	char m_keys[256];

public:

	bool Left, Right, Z;

	// �R���X�g���N�^
	CInput( HWND hWnd );
	~CInput();

	// �L�[���͂̏�Ԃ��擾
	void UpdataState();

	// ����������Ă��Ȃ���Ԃɂ���
	void Clear();
};

#endif