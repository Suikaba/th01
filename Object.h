#ifndef BLOCK_H
#define BLOCK_H

#include <d3dx9.h>

#define MAX_BLOCK 81
#define BLOCK_WIDTH 32
#define BLOCK_HEIGHT 16
#define BLOCK_TATENOKAZU 9
#define BLOCK_YOKONOKAZU 9
#define BAR_WIDTH 64
#define BAR_HEIGHT 16
#define BALL_WIDTH 16
#define BALL_HEIGHT 16

class CObject {
private:

	LPDIRECT3DTEXTURE9 BlockTex; // �u���b�N�̃e�N�X�`��
	struct Block {
		float x, y; // ���W
		bool flag; // ���邩�Ȃ���
	};

	struct Ball {
		float x, y; // ���W
		float angle; // �p�x
		LPDIRECT3DTEXTURE9 BallTex; // �{�[���̃e�N�X�`��
		float PrevX, PrevY;
	};

	struct Bar {
		float x, y; // ���W
		LPDIRECT3DTEXTURE9 BarTex; // �o�[�̃e�N�X�`��
	};

	// �E�B���h�E�̕��A����
	int WindowWidth, WindowHeight;

	// �{�[���̑��x
	float BallSpeed;

public:

	// �R���X�g���N�^
	CObject( int w, int h );
	~CObject();

	Block block[MAX_BLOCK];
	Ball ball;
	Bar bar;

	void SetBlockTexture( LPDIRECT3DTEXTURE9 texture ) { BlockTex = texture; }
	void SetBarTexture( LPDIRECT3DTEXTURE9 texture ) { bar.BarTex = texture; }
	void SetBallTexture( LPDIRECT3DTEXTURE9 texture ) { ball.BallTex = texture; }

	Block GetBlock( int i ) { return block[i]; }
	Bar GetBar() { return bar; }
	Ball GetBall() { return ball; }
	LPDIRECT3DTEXTURE9 GetBlockTexture() { return BlockTex; }

	// �I�u�W�F�N�g�̕`��
	virtual void DrawObject() {}

	// �I�u�W�F�N�g�̈ړ�
	void MoveBar( bool l, bool r );
	void MoveBall();

	// �u���b�N���ʂƂ������Ă��������
	void CheckBlock();

	bool CheckClear();

	bool GameOver();

	// �I�u�W�F�N�g�̏�Ԃ̃��Z�b�g
	void ResetObject();

};

#endif 