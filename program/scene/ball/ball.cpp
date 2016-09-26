#include "ball.h"

float rand01()
{
	return static_cast<float>(rand()%201)/200.0f;
}

void BALL::Init(const SHELL* shell, const SCENE_PROPERTIES& bip) noexcept
{
	radius = 
		bip.radius_min + rand01() * (bip.radius_max - bip.radius_min);

	mass =
		bip.mass_radius_equivalent ? radius : 
		bip.mass_min + rand01() * (bip.mass_max - bip.mass_min);

	if (shell)
	{
		position = 
		{
			(2*rand01() - 1)*(shell->size - radius),
			(2*rand01() - 1)*(shell->size - radius),
			(2*rand01() - 1)*(shell->size - radius)
		};
	}
	else
	{
		position = 
		{
			(2*rand01() - 1)*bip.dist_from_center,
			(2*rand01() - 1)*bip.dist_from_center,
			(2*rand01() - 1)*bip.dist_from_center
		};
	}

	material = 
		static_cast<MATERIAL_TYPE>(bip.material_id_min + rand() % (bip.material_id_max - bip.material_id_min + 1));

	speed = 
		{ 2*rand01() - 1, 2*rand01() - 1, 2*rand01() - 1 };
	speed /= sqrt(speed.x*speed.x + speed.y*speed.y + speed.z*speed.z);
	speed *= bip.speed_min + rand01() * (bip.speed_max - bip.speed_min);
}
bool BALL::BallIsCorrect(const std::vector<BALL*>& balls, const SHELL* shell, const SCENE_PROPERTIES& bip) const noexcept
{
	for (auto it = balls.begin(); it != balls.end(); it++)
	{
		if (*it == this)
			continue;

		if (DistanceToBall(*it) <= radius + (*it)->radius)
			return false;

		if (bip.material_exclusiveness && material == (*it)->material)
			return false;
	}

	return true;
}

BALL::BALL(GRAPHICS* graphics,
		   const std::vector<BALL*>& balls,
		   const SHELL* shell,
		   const SCENE_PROPERTIES& bip) : graphics(graphics)
{
	for (unsigned trial = 0;; trial++)
	{
		Init(shell, bip);

		if (BallIsCorrect(balls, shell, bip))
			break;
		
		if (trial >= 200)
			throw 0;
	}
}

void BALL::Move() noexcept
{
	position += speed*graphics->RetTimerInterval();
}
void BALL::Render() noexcept
{
	graphics->SetWorld(position, radius);
	graphics->Dev()->SetMaterial(graphics->RetMaterial(material));
	graphics->DrawShape(ST_SPHERE);
}

