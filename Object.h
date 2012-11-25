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

	LPDIRECT3DTEXTURE9 BlockTex; // ブロックのテクスチャ
	struct Block {
		float x, y; // 座標
		bool flag; // あるかないか
	};

	struct Ball {
		float x, y; // 座標
		float angle; // 角度
		LPDIRECT3DTEXTURE9 BallTex; // ボールのテクスチャ
		float PrevX, PrevY;
	};

	struct Bar {
		float x, y; // 座標
		LPDIRECT3DTEXTURE9 BarTex; // バーのテクスチャ
	};

	// ウィンドウの幅、高さ
	int WindowWidth, WindowHeight;

	// ボールの速度
	float BallSpeed;

public:

	// コンストラクタ
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

	// オブジェクトの描画
	virtual void DrawObject() {}

	// オブジェクトの移動
	void MoveBar( bool l, bool r );
	void MoveBall();

	// ブロックが玉とあたっていたら消去
	void CheckBlock();

	bool CheckClear();

	bool GameOver();

	// オブジェクトの状態のリセット
	void ResetObject();

};

#endif 