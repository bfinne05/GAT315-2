#pragma once
#include "glm/glm.hpp"

struct Contact
{
	class Body* BodyA{ nullptr };
	class Body* BodyB{ nullptr };

	float restitution{ 0 };
	float depth{ 0 };
	glm::vec2 normal{ 0,0 };
};