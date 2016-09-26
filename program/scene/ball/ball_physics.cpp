#include "ball.h"

float operator* (const D3DXVECTOR3& v1, const D3DXVECTOR3& v2)
{
	return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
float signum (float x)
{
	if (x == 0)
		return 0.0f;
	else if (x > 0)
		return 1.0f;
	else return -1.0f;
}

float BALL::DistanceToBall(const BALL* ball) const noexcept
{
	return sqrt((position - ball->position)*(position - ball->position));
}

void BALL::Collisions(const std::vector<BALL*>& balls, SHELL* shell) noexcept
{
	// collisions with walls
	if (shell)
	{
		if (position.x >= shell->size - radius)
			speed.x = -abs(speed.x);
		if (position.y >= shell->size - radius)
			speed.y = -abs(speed.y);
		if (position.z >= shell->size - radius)
			speed.z = -abs(speed.z);

		if (position.x <= radius - shell->size)
			speed.x = abs(speed.x);
		if (position.y <= radius - shell->size)
			speed.y = abs(speed.y);
		if (position.z <= radius - shell->size)
			speed.z = abs(speed.z);
	}
	
	// collisions with balls
	for (auto it = balls.begin(); it != balls.end(); it++)
		if (*it != this)
		{
			D3DXVECTOR3 shift = (*it)->position - position;
			D3DXVECTOR3 normal = shift / sqrt(shift*shift);

			if (shift*shift <= ((*it)->radius + radius)*((*it)->radius + radius))
			{
				D3DXVECTOR3 relative_speed = (*it)->speed - speed;

				if (shift*relative_speed < 0)
				{
					float v_ball = normal * (*it)->speed;
					float v_this = normal * speed;

					float P = (*it)->mass*v_ball        + mass*v_this;
					float E = (*it)->mass*v_ball*v_ball + mass*v_this*v_this;
					float D = (*it)->mass*mass*(E*((*it)->mass+mass)-P*P);

					(*it)->speed += ((P*(*it)->mass + sqrt(D)) / ((*it)->mass*(mass + (*it)->mass)) - v_ball)*normal;
						   speed += ((P   *    mass - sqrt(D)) /        (mass*(mass + (*it)->mass)) - v_this)*normal;
				}
			}
		}
}

float BALL::G = 0;
void BALL::Gravity(const std::vector<BALL*>& balls) noexcept
{
	D3DXVECTOR3 gravity_acceleration(0, 0, 0);

	for (auto it = balls.begin(); it != balls.end(); it++)
		if (*it != this)
		{
			float r = DistanceToBall(*it);
			gravity_acceleration += G*(*it)->mass*((*it)->position - position) / (r*r*r);
		}

	speed += gravity_acceleration*graphics->RetTimerInterval();
}

