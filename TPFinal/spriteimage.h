#pragma once

#include <d3dx9.h>
#include <string>


class SpriteImage
{
public:
	SpriteImage(void);
	SpriteImage(float x, float y);
	~SpriteImage(void);

	// sprite functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();
	virtual void Draw();

private:
	LPDIRECT3DTEXTURE9 _texture;
	LPD3DXSPRITE _sprite;

	D3DXVECTOR3 _position;
	D3DCOLOR _color;
	bool _isInitialized;

};