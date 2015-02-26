#include "spriteimage.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG 

SpriteImage::SpriteImage(void)
{

	_position.x = 0;
	_position.y = 0;
	_position.z = 0;

	_color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_isInitialized = false;

}

SpriteImage::SpriteImage(float x, float y)
{
	
	_position.x = x;
	_position.y = y;
	_position.z = 0;

	_color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_isInitialized = false;

}
	

SpriteImage::~SpriteImage(void)
{

	if( _sprite != NULL )
	{
		_sprite->Release();
		_sprite = NULL;
	}
	if( _texture != NULL )
	{
		_texture->Release();
		_texture = NULL;
	}

}


bool SpriteImage::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{

	if( FAILED( D3DXCreateTextureFromFileEx(
			device, 
			file.c_str(),
			width, height,
			D3DX_DEFAULT, 0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT,
			0, NULL, NULL,
			&_texture)))
				return false;

	if( FAILED( D3DXCreateSprite(device, &_sprite)))
		return false;

	_isInitialized = true;

	return true;

}

bool SpriteImage::IsInitialized()
{
	return _isInitialized;
}

void SpriteImage::Draw()
{
	if( _sprite && _texture )
	{
		_sprite->Begin(D3DXSPRITE_ALPHABLEND);

		_sprite->Draw(_texture, NULL, NULL, &_position, _color);

		_sprite->End();
	}
}




