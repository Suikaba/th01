#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <windows.h>
#include "Graphics.h"
#include "Input.h"
#include "Object.h"
#include <tchar.h>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 400


//=================================================================
// �E�B���h�E�̖{�̂̃N���X
class CWindowBase {
private:

	// �E�B���h�E�n���h��
	HWND hWnd, DesktophWnd;

	// �A�v���P�[�V������
	string AppName;

	// �O���t�B�N�X
	CGraphics* Graphics;

	// �I�u�W�F�N�g�i�u���b�N�A�o�[�A�{�[���j
	CObject* Object;

	// �L�[���
	CInput* Input;

	// ���j���[�̃e�N�X�`��
	LPDIRECT3DTEXTURE9 menu;
	LPDIRECT3DTEXTURE9 gameover;
	LPDIRECT3DTEXTURE9 clear;

	void DrawScene();

	void DrawMenu();
	void DrawClear();
	void DrawGameOver();

	enum shikensu {
		MENU,
		GAMEMAIN,
		CLEAR,
		GAMEOVER,
	};

	int shikensu;

	DWORD time;

public:

	// �R���X�g���N�^
	CWindowBase( HINSTANCE hInstance, LPCTSTR appname );
	~CWindowBase();

	// ���b�Z�[�W�n���h��
	virtual LRESULT CALLBACK WndProc( UINT msg, WPARAM wParam, LPARAM lParam );

	// �I�u�W�F�N�g�̃e�N�X�`���̃��[�h
	void SetObjectTexture();

	// ��ʂ̃��Z�b�g
	void ResetScreen();

	// �L�[���͂̍X�V
	void InputUpdate();

	virtual void ObjectDraw();

	// �N���A���Ă邩�ǂ����m�F
	void ClearCheck();

	// �Q�[���̎��s
	void Run();

	void Move();

	// �Q�[���I�[�o�[���ǂ���
	void CheckGameOver();

	// �V�[�P���X�̓���ւ�
	void ShikensuChenge();

};


#endif

