#pragma once
#include "Framework.h"
#include "Vec2.h"
#include "Rect.h"
#include "AssetManager.h"
class Hero
{
public:
	Hero(const Vec2& pos);

	void Draw() const;
	void Update(class Game& Game);

	void Kill();

	void Shoot(Vec2 MousePos);
	void ProcessBullet( class Game& Game);

	RectF GetHitbox() const;
	RectF GetTHold()const;

	inline const Vec2& GetPos() const { return pos;		}
	inline const bool isDead()		  { return isdead;  };

private:
	Vec2 pos = { 0.0f,0.0f };

	// this is data for the bullet that will be fired
	Vec2 bulletDir			=	{ 0.0f,0.0f };
	Vec2 bulletSpawnPos		=	{ 0.0f,0.0f };

	// this flag is set during input processing to indicate a bullet should
	// be spawned on update
	bool isFiring = false;

	float hitbox_halfwidth		=	14.0f;
	float hitbox_halfheight		=	12.0f;
	float treshhold_halfwidth	=	250.0f;
	float treshhold_halfheight	=	200.0f;

	bool isdead		=	false;

	Sprite* sprite	 =	AssetManager::Instance()->GetSprite("avatar.jpg");;
	Vec2 draw_offset = { -18.0f,-17.0f };
};