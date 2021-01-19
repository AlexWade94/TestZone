#include "Game.h"
#include <iostream>
#include "Util.h"
Game::Game(Vec2 ScreenSize, Vec2 mapsize, int ecount, int bcount)
	:
	state (GameState::START),
	camerapos			( { ScreenSize.x / 2 ,  ScreenSize.y / 2 } ),
	hero				( { ScreenSize.x / 2 ,  ScreenSize.y / 2 } ),
	bulletcount (bcount),
	enemycount	(ecount),
	topleftborder		( { 0 - ((mapsize.x - ScreenSize.x) / 2.0f),			0 - ((mapsize.y - ScreenSize.y) / 2.0f) } ),
	bottomrightborder	( { ScreenSize.x + ((mapsize.x - ScreenSize.x) / 2.0f), ScreenSize.y + ((mapsize.y - ScreenSize.y) / 2.0f) } )
{

	//random inbound coords for each enemy
	std::uniform_real_distribution<float> xd(topleftborder.x, bottomrightborder.x);
	std::uniform_real_distribution<float> yd(topleftborder.y, bottomrightborder.y);
	
	//tempopary coords for hero trashhold check
	Vec2 enemypos;

	for (int n = 0; n < enemycount; n++)
	{
		enemypos = { xd(rng),yd(rng) };
		//while enemy is to close--generate new coords for enemy
		while(hero.GetTHold().Contains(enemypos))
		{
			enemypos = { xd(rng),yd(rng) };
		}
		//emplace if far enough
		enemies.emplace_back(enemypos);
	}
}

void Game::Draw() const
{
	hero.Draw();
	for (const auto& i : bullets)
	{
		i.Draw();
	}
	for (const auto& i : enemies)
	{
		i.Draw();
	}

	//4 boundaries indicators
	drawSprite(sprite, (int)topleftborder.x     + (int)deltacam.x, (int)topleftborder.y		+ (int)deltacam.y);
	drawSprite(sprite, (int)topleftborder.x     + (int)deltacam.x, (int)bottomrightborder.y + (int)deltacam.y);
	drawSprite(sprite, (int)bottomrightborder.x + (int)deltacam.x, (int)bottomrightborder.y + (int)deltacam.y);
	drawSprite(sprite, (int)bottomrightborder.x + (int)deltacam.x, (int)topleftborder.y		+ (int)deltacam.y);
}

void Game::SetVel(Vec2 v)
{
	vel = v.GetNormalized();
	vel*= speed;
	
}

void Game::SetState(const GameState& st)
{
	state = st; 
}

void Game::Reset()
{
	//reset camera to default
	camerapos += deltacam;
	deltacam = { 0.0f,0.0f };

	//delete bullets and enemies
	enemies.erase(enemies.begin(), enemies.end());
	bullets.erase(bullets.begin(), bullets.end());

	//re-emplace enemies
	std::uniform_real_distribution<float> xd(topleftborder.x, bottomrightborder.x);
	std::uniform_real_distribution<float> yd(topleftborder.y, bottomrightborder.y);

	Vec2 enemypos;
	for (int n = 0; n < enemycount; n++)
	{
		enemypos = { xd(rng),yd(rng) };
		while (hero.GetTHold().Contains(enemypos))
		{
			enemypos = { xd(rng),yd(rng) };
		}
		enemies.emplace_back(enemypos);
	}
}

void Game::Update(float dt)
{

	//move the camera inside borders, offset enemies based on camera movement
	if (camerapos.x > topleftborder.x && camerapos.x < bottomrightborder.x && camerapos.y > topleftborder.y && camerapos.y < bottomrightborder.y)
	{
		
		for (auto& i : enemies)
		{
			i.DisplaceBy(-vel*dt);
			i.Update(*this, dt);
			i.ProcessLogic(*this);
		}
		camerapos += vel*dt;
		deltacam -= vel*dt;
	}

	//collision with borders
	if (camerapos.x <= topleftborder.x)
	{
		for (auto& i : enemies)
		{
			i.DisplaceBy({ vel.x * dt,0.0f });
			i.ProcessLogic(*this);
		}
		camerapos.x += -vel.x*dt;
		deltacam.x  -= -vel.x*dt;
	}
	if (camerapos.y <= topleftborder.y)
	{
		for (auto& i : enemies)
		{
			i.DisplaceBy({ 0.0f,vel.y * dt });
			i.ProcessLogic(*this);
		}
		camerapos.y += -vel.y*dt;
		deltacam.y  -= -vel.y*dt;
	}
	if (camerapos.x >= bottomrightborder.x)
	{
		for (auto& i : enemies)
		{
			i.DisplaceBy({ vel.x * dt,0.0f });
			i.ProcessLogic(*this);
		}
		camerapos.x -= vel.x*dt;
		deltacam.x  += vel.x*dt;
	}
	if (camerapos.y >= bottomrightborder.y)
	{

		for (auto& i : enemies)
		{
			i.DisplaceBy({ 0.0f,vel.y * dt });
			i.ProcessLogic(*this);
		}
		camerapos.y -=  vel.y*dt;
		deltacam.y  += vel.y*dt;
	}


	hero.Update(*this);

	for (auto& i : bullets)
	{
		i.Update(dt);
		i.DisplaceBy(vel * dt);
	}

	for (auto& enemie : enemies)
	{
		// tests for collision between enemie and bullet/hero
		// only do tests if enemie is alive
		if (!enemie.IsReadyForRemoval())
		{
			// calculate the enemie hitbox once here
			const auto enemie_hitbox = enemie.GetHitbox();
		
			// hero dies if collides with enemie
			if (hero.GetHitbox().IsOverlappingWith(enemie.GetHitbox()))
			{
				hero.Kill();
				SetState(GameState::LOSE);
				enemycount -= 10;
				if (enemycount < 1)
					enemycount = 10;
			}

				// remove all bullets colliding with current enemie
				remove_erase_if(bullets,
				// capture enemie so we can damage it on bullet collision
				[&enemie, &enemie_hitbox](const Bullet& b)
				{
					if (b.GetHitbox().IsOverlappingWith(enemie_hitbox))
					{
						enemie.Kill();
						return true;
					}
					return false;
				}
			);
			
		}
	
	}
	remove_erase_if(enemies, std::mem_fn(&Enemy::IsReadyForRemoval));

	if (enemies.size() == 0)
	{
		enemycount += 10;
		SetState(GameState::WIN);
	}

}
void Game::SpawnBullet(Bullet bullet)
{
	if (bullets.size() == bulletcount)
	{
		bullets.erase(bullets.begin());
	}
	bullets.push_back(bullet);
}

