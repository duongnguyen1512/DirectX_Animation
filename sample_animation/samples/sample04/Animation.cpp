#pragma once

#include"Animation.h"

Animation::Animation(GTexture *texture, LPDIRECT3DDEVICE9 d3dv, int SpritePerRow, int Count)
{
	this->kitty_left = new GTexture(d3dv, KITTY_IMAGE_LEFT);
	this->kitty_right = new GTexture(d3dv, KITTY_IMAGE_RIGHT);

	this->_SpritePerRow = SpritePerRow;
	this->_Count = Count;
	this->_Index = 0;
	this->x = 0;
	this->y = GROUND_Y;
	
	this->Load(kitty_left);
	this->Load(kitty_right);
}

void Animation::Load(GTexture* texture)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(texture->FileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	texture->Size = s;

	texture->FrameWidth = info.Width / this->_SpritePerRow;
	texture->FrameHeight = info.Height / (this->_Count / this->_SpritePerRow);

	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
		//GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
		//OutputDebugString(FileName);
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		texture->d3dv,
		texture->FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), //color
		&info,
		NULL,
		&texture->Texture
		);

	if (result != D3D_OK)
	{
		/*GLMessage("Can not load texture/*");
		GLTrace("[texture.h] Failed to create texture from file '%s', FileName);*/
		return;
	}
}



void Animation::Render(VideoDriver *video, GTexture *texture)
{
	RECT srect;

	srect.left = (this->_Index % _SpritePerRow)*(texture->FrameWidth) + 1;
	srect.top = (this->_Index / _SpritePerRow)*(texture->FrameHeight) + 1;
	srect.right = srect.left + texture->FrameWidth;
	srect.bottom = srect.top + texture->FrameHeight + 1;

	video->DrawSprite(this->x, GROUND_Y, texture, srect);
}

void Animation::Next()
{
	_Index = (_Index + _Count - 1) % _Count;
}

void Animation::Reset()
{
	_Index = 0;
}

void Animation::Render_Object_Left(VideoDriver *video)
{
	this->Render(video, this->kitty_left);
}

void Animation::Render_Object_Right(VideoDriver *video)
{
	this->Render(video, this->kitty_right);
}