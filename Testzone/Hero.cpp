#include "Hero.h"
#include "Game.h"
#include "iostream"
Hero::Hero(const Vec2& pos)
	:
	pos(pos)
{
}

RectF Hero::GetHitbox() const
{
	return RectF::FromCenter(pos, hitbox_halfwidth, hitbox_halfheight);
}

RectF Hero::GetTHold() const
{
	return RectF::FromCenter(pos, treshhold_halfwidth, treshhold_halfheight);
}

void Hero::Draw() const
{
	drawSprite(sprite, (int)pos.x+(int)draw_offset.x, (int)pos.y+(int)draw_offset.y);
}

void Hero::Kill()
{

		isdead = true;

}


void Hero::Update(Game& Game)
{
	ProcessBullet(Game);
}

void Hero::Shoot(Vec2 MousePos)
{
	bulletSpawnPos = GetPos();

	bulletDir = MousePos - bulletSpawnPos;

	if (bulletDir == Vec2{ 0.0f,0.0f })
	{
		bulletDir = { 0.0f,1.0f };
	}

	else
	{
		bulletDir.Normalize();
	}
	isFiring = true;
	
}

void Hero::ProcessBullet(Game& Game)
{
	if (isFiring)
	{
		isFiring = false;
		Game.SpawnBullet({ bulletSpawnPos,bulletDir });
	}
}


