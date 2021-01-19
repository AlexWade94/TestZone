#include "MyFrameWork.h"


/* Test Framework realization */

MyFramework::MyFramework(int S_WIDTH, int S_HEIGHT, int M_WIDTH, int M_HEIGHT, int N_ENEMIES, int N_AMMO)
	:
	SCREEN_WIDTH(S_WIDTH),
	SCREEN_HEIGHT(S_HEIGHT),
	MAP_WIDTH(M_WIDTH),
	MAP_HEIGHT(M_HEIGHT),
	NUM_ENEMIES(N_ENEMIES),
	NUM_AMMO(N_AMMO)
{

	//if window size settings are too big/small or gamefield is too small, reajust it
	if (SCREEN_WIDTH < 700 || SCREEN_WIDTH>2000)
	{
		SCREEN_WIDTH = 700;
	}
	if (SCREEN_HEIGHT < 480 || SCREEN_HEIGHT>2000)
	{
		SCREEN_HEIGHT = 480;
	}
	if (MAP_WIDTH < 600 )
	{
		MAP_WIDTH = 600;
	}
	if (MAP_HEIGHT < 500 )
	{
		MAP_HEIGHT = 500;
	}

	//ammo and enemies can't be less than 1
	if (NUM_ENEMIES < 1)
	{
		NUM_ENEMIES = 10;
	}
	if (NUM_AMMO < 1)
	{
		NUM_AMMO = 1;
	}
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width		=	SCREEN_WIDTH;
	height		=	SCREEN_HEIGHT;
	fullscreen	=	false;
}

bool MyFramework::Init()
{
	//initilize game by screen and map sizes, amount of enemies and ammo
	game	=	new Game({ (float)SCREEN_WIDTH,(float)SCREEN_HEIGHT }, { (float)MAP_WIDTH , (float)MAP_HEIGHT }, NUM_ENEMIES, NUM_AMMO);

	cursor	=	 AssetManager::Instance()->GetSprite("circle.tga");
	pause	=	 AssetManager::Instance()->GetSprite("icon.png");
	lose	=	 AssetManager::Instance()->GetSprite("gameover.png");
	start	=	 AssetManager::Instance()->GetSprite("start.png");
	win		=	 AssetManager::Instance()->GetSprite("win.png");

	showCursor(false);

	//obtaining cursor sprite size for a proper cursor display
	getSpriteSize(cursor,  mouse_w,  mouse_h);
	mouse_w /= 2;
	mouse_h /= 2;

	//calculating proper gamestate icon coords
	getSpriteSize(pause,   pause_w,  pause_h);
	getSpriteSize(lose,    lose_w,   lose_h);
	getSpriteSize(start,   start_w,  start_h);
	getSpriteSize(win,	   win_w,    win_h);

	pause_w = SCREEN_WIDTH	/ 2 - pause_w / 2;
	pause_h = SCREEN_HEIGHT / 2 - pause_h / 2;

	lose_w = SCREEN_WIDTH	/ 2 - lose_w / 2;
	lose_h = SCREEN_HEIGHT	/ 2 - lose_h / 2;

	start_w = SCREEN_WIDTH	/ 2 - start_w / 2;
	start_h = SCREEN_HEIGHT / 2 - start_h / 2;

	win_w = SCREEN_WIDTH	/ 2 - win_w / 2;
	win_h = SCREEN_HEIGHT	/ 2 - win_h / 2;

	return true;
}

void MyFramework::Close()
{
	AssetManager::Release();

	cursor	= nullptr;
	pause	= nullptr;
	lose	= nullptr;
	start	= nullptr;
	win		= nullptr;

	delete game;
}

bool MyFramework::Tick()
{

	#ifdef _DEBUG
		if(game->GetState()==GameState::RUN)
		game->Draw();
	#endif 

	float elapsedTime = ft.Mark();

	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		switch (game->GetState())
		{

		case GameState::RUN:

		#ifdef NDEBUG
			game->Draw();
		#endif 

			game->SetVel(vel);
			game->Update(dt);
			break;

		case GameState::START:

			drawSprite(start, start_w, start_h);
			break;

		case GameState::PAUSE:

			drawSprite(pause, pause_w, pause_h);
			break;

		case GameState::LOSE:

			drawSprite(lose, lose_w, lose_h);
			break;

		case GameState::WIN:

			drawSprite(win, win_w,  win_h);
			break;

		}
		elapsedTime -= dt;

	}
	drawSprite(cursor, (int)mousepos.x, (int)mousepos.y);

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	//mouse pos adjusted to it's center instead of top left tip
	mousepos = { (float)(x - mouse_w),(float)(y - mouse_h) };
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	switch (game->GetState())
	{
	case GameState::RUN:

		if (button == FRMouseButton::LEFT && !isReleased)
		{
			game->GetHero().Shoot(mousepos);
		}
		if (button == FRMouseButton::RIGHT && !isReleased)
		{
			game->SetState(GameState::PAUSE);
			return;
		}
		if (button == FRMouseButton::MIDDLE && !isReleased)
		{
			game->SetState(GameState::LOSE);
		}
		break;

	case GameState::START:

		if (button == FRMouseButton::RIGHT && !isReleased)
		{
			game->SetState(GameState::RUN);
			return;
		}
		break;

	case GameState::PAUSE:

		if (button == FRMouseButton::RIGHT && !isReleased)
		{
			game->SetState(GameState::RUN);
			return;
		}
		break;

		//procede to start screen if you won or lost
	case GameState::WIN:
	case GameState::LOSE:

		if (button == FRMouseButton::RIGHT && !isReleased)
		{
			game->Reset();
			game->SetState(GameState::START);
			return;
		}
		break;

	}
}

void MyFramework::onKeyPressed(FRKey k)
{
	if (k == FRKey::LEFT)
	{
		vel += {-1.0f, 0.0f };
	}
	if (k == FRKey::RIGHT)
	{
		vel += { 1.0f, 0.0f };
	}
	if (k == FRKey::UP)
	{
		vel += { 0.0f, -1.0f };
	}
	if (k == FRKey::DOWN)
	{
		vel += { 0.0f, 1.0f };
	}
}

void MyFramework::onKeyReleased(FRKey k)
{
	if (k == FRKey::LEFT)
	{
		vel -= {-1.0f, 0.0f };
	}
	if (k == FRKey::RIGHT)
	{
		vel -= { 1.0f, 0.0f };
	}
	if (k == FRKey::UP)
	{
		vel -= { 0.0f,-1.0f };
	}
	if (k == FRKey::DOWN)
	{
		vel -= { 0.0f, 1.0f };
	}
}


