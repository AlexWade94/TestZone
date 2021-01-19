#include "Enemy.h"
#include "Game.h"
Enemy::Enemy(const Vec2& pos)
	:
	pos(pos)
{
	
}

const void Enemy::Draw() const
{
	drawSprite(sprite, (int)pos.x, (int)pos.y);
}

void Enemy::ProcessLogic(const Game& Game)
{
	// flag for avoidance state
	bool avoiding = false;

	// if close to any enemy, avoid it
	for (auto& other : Game.GetEnemiesConst())
	{
		// don't consider self
		if (this == &other)
		{
			continue;
		}

		const auto delta = GetPos() - other.GetPos();
		const auto lensq = delta.GetLengthSq();

		if (lensq < 500.0f)
		{
			// avoiding state set
			avoiding = true;
			// case for enemies at same location
			if (lensq == 0.0f)
			{
				SetDirection({ -1.0f,1.0f });
			}
			else
			{
				SetDirection(delta / std::sqrt(lensq));
			}
			break;
		}
	}
	// check if in avoidance state, if so do not pursue
	if (!avoiding)
	{
		const Vec2 delta = Game.GetHeroConst().GetPos()-GetPos();

		// we only wanna move if not already really close to target pos
		// (prevents vibrating around target point;)
		if (delta.GetLengthSq() > 3.0f)
		{
			SetDirection(delta.GetNormalized());
		}
		else
		{
			SetDirection({ 0.0f,0.0f });
		}
	}
}


void Enemy::Update(const Game& Game, float dt)
{
	// dead enemies tell no tales (or even move for that matter)
	if(!IsReadyForRemoval())
	pos += vel*dt;
}

void Enemy::Kill()
{
	isDead = true;
}

RectF Enemy::GetHitbox() const
{
	return RectF::FromCenter(pos, hitbox_halfwidth, hitbox_halfheight);
}


void Enemy::DisplaceBy(const Vec2& d)
{
	pos += d;
}

void Enemy::SetDirection(const Vec2& dir)
{
	vel = dir * speed;
}
