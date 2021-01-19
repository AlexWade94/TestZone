#pragma once
#include "Framework.h"
#include <iostream>
#include "hero.h"
#include "Vec2.h"
#include "Game.h"
#include "FrameTimer.h"
#include "AssetManager.h"
#include <memory>

/* Test Framework realization */
class MyFramework : public Framework 
{
public:
	//setting up window and game
	MyFramework(int SCREEN_WIDTH, int SCREEN_HEIGHT, int MAP_WIDTH, int MAP_HEIGHT, int NUM_ENEMIES, int NUM_AMMO );
	//iniit window parameters
	virtual void PreInit(int& width, int& height, bool& fullscreen) override;

	//init game data
	virtual bool Init() override;

	//what to do every frame
	virtual bool Tick() override;

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	virtual void onKeyPressed(FRKey k) override;
	virtual void onKeyReleased(FRKey k) override;
		
	virtual void Close() override;

private:
	FrameTimer ft;

	//velocity of the ingame camera controlled by keyboard
	Vec2 vel = { 0.0f,0.0f };

	//game instance
	Game* game=nullptr;

	//mouse
	Sprite* cursor = nullptr;
	Vec2 mousepos{ 0.0f,0.0f };

	//width and height of mouse sprite for right cursor offset
	int mouse_w = 0;
	int mouse_h = 0;

	//game settings
	int SCREEN_WIDTH  =		1440;
	int SCREEN_HEIGHT =		720;

	int MAP_WIDTH     =		1200;
	int MAP_HEIGHT    =		1200;

	int NUM_AMMO	  =		3;
	int NUM_ENEMIES   =		40;

	//gamestate sprites
	Sprite* start = nullptr;
	int start_w = 0;
	int start_h = 0;

	Sprite* pause = nullptr;
	int pause_w = 0;
	int pause_h = 0;

	Sprite* lose  = nullptr;
	int lose_w = 0;
	int lose_h = 0;

	Sprite* win   = nullptr;
	int win_w = 0;
	int win_h = 0;

};
