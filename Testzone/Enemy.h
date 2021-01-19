#pragma once
#include "Framework.h"
#include "Vec2.h"
#include "Rect.h"
#include "AssetManager.h"
class Enemy
{
public:
	Enemy(const Vec2& pos);

	const void Draw() const;
	void	   Update(const class Game& Game, float dt);
	void	   ProcessLogic(const class Game& Game);

	void	   Kill();
	void	   DisplaceBy(const Vec2& d);
	RectF	   GetHitbox() const;

	inline const Vec2&	 GetPos() const { return pos; };
	inline const bool	 IsReadyForRemoval() const { return isDead; };

private:
	void SetDirection(const Vec2& dir);

private:
	Vec2 pos { 0.0f,0.0f };
	Vec2 vel { 0.0f,0.0f };

	float hitbox_halfwidth  = 16.0f;
	float hitbox_halfheight = 7.0f;

	float speed = 120.0f;
	
	bool isDead=false;

	Sprite* sprite=AssetManager::Instance()->GetSprite("enemy.png");
	Vec2 draw_offset = { -11.0f,-19.0f };
};