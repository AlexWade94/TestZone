#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Framework.h"
#include "AssetManager.h"
class Bullet
{
public:
	Bullet(const Vec2& pos, const Vec2& dir)
		:
		pos(pos),
		vel(dir* speed)
	{
	}
	void Draw() const
	{
		//draw bullet sprite based on the centre of object
		drawSprite(sprite, (int)(pos.x+draw_offset.x), int(pos.y+draw_offset.y));
		const auto draw_pos = pos + draw_offset;
	}
	void Update(float dt)
	{
		pos += vel*dt;
	}
	const Vec2& GetPos() const
	{
		return pos;
	}
	RectF GetHitbox() const
	{
		return RectF::FromCenter(pos, hitbox_halfwidth, hitbox_halfheight);
	}
	void DisplaceBy(const Vec2& d)
	{
		pos -= d;
	}
private:

	float speed = 400.0f;
	
	Vec2 pos		  { 0.0f, 0.0f };
	Vec2 vel          { 0.0f, 0.0f };
	Vec2 draw_offset  { 8.0f, 8.0f };

	float hitbox_halfwidth	= 4.0f;
	float hitbox_halfheight = 4.0f;

	Sprite* sprite= AssetManager::Instance()->GetSprite("bullet.png");
};