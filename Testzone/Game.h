#pragma once
#include "Framework.h"
#include "Vec2.h"
#include "Hero.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AssetManager.h"
#include <iostream>
#include <vector>
#include <functional>
#include <random>


enum class GameState
{
	START,
	PAUSE,
	WIN,
	LOSE,
	RUN
};

class Game
{
public:
	Game(Vec2 ScreenSize, Vec2 mapsize, int enemycount, int bulletcount);

	void	Update(float dt);
	void	Draw() const;

	//resets enemies, bullets and camera position to starting settings
	void	Reset();

	void	SetVel(Vec2 vel);
	void	SetState(const GameState& st);
	void	SpawnBullet(Bullet bullet);

	inline Hero&			  GetHero() {							return hero; };
	inline const Hero&		  GetHeroConst() const {				return hero; };
	inline const std::vector<Enemy>& GetEnemiesConst() const {		return enemies; }

	//Velocity of camera
	inline const Vec2&		  GetVel() const {						return vel; };
	inline const GameState    GetState() const {					return state;}



private:

	//rng for enemy coords
	std::mt19937 rng = std::mt19937(std::random_device{}());

	//sprite for boundaries
	Sprite* sprite=AssetManager::Instance()->GetSprite("reticle.png");
	
	//For bounds moving
	Vec2 deltacam	       { 0.0f, 0.0f };

	//For colission detection with borders and enemies
	Vec2 camerapos         { 0.0f, 0.0f };
	
	//velocity of the camera
	Vec2 vel			   { 0.0f, 0.0f };

	//camera speed
	float speed = 220.0f;

	//borders
	Vec2 topleftborder	   { 0.0f, 0.0f };
	Vec2 bottomrightborder { 0.0f, 0.0f };

	//game objects
	Hero hero;
	std::vector<Bullet> bullets;
	std::vector<Enemy>	enemies;

	int bulletcount = 0;
	int enemycount  = 0;

	//Active state of the game
	GameState state;
};