#pragma once

#include "..\\..\\graphics\\graphics.h"
#include "..\\shell\\shell.h"
#include "..\\scene_properties.h"

class BALL
{
	static float G;

	GRAPHICS* graphics;

	float radius;
	float mass;
	D3DXVECTOR3 position;
	MATERIAL_TYPE material;
	D3DXVECTOR3 speed;

	float DistanceToBall(const BALL* ball) const noexcept;

	inline void Init(const SHELL* shell, const SCENE_PROPERTIES& sp) noexcept;
	inline bool BallIsCorrect(const std::vector<BALL*>& balls, const SHELL* shell, const SCENE_PROPERTIES& sp) const noexcept;

	BALL(GRAPHICS* graphics, const std::vector<BALL*>& balls, const SHELL* shell, const SCENE_PROPERTIES& sp);
	BALL(const BALL&) = delete;
	BALL& operator= (const BALL&) = delete;

	void Collisions(const std::vector<BALL*>& balls, SHELL* shell) noexcept;
	void Gravity(const std::vector<BALL*>& balls) noexcept;
	void Move() noexcept;
	void Render() noexcept;

	friend class SCENE;
};