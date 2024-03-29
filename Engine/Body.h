#pragma once
#include <glm/glm.hpp>

class Body
{
public:
	enum Type
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

public:
	Body(class Shape* shape, const glm::vec2& position, const glm::vec2& velocity = { 0, 0 }, float mass = 1, Type type = Type::DYNAMIC) :
		shape{ shape },
		position{ position },
		velocity{ velocity },
		mass{ mass },
		type{ type }
	{
		//if (type == STATIC) mass = 0;
		invMass = (mass == 0 || type != DYNAMIC) ? 0 : 1 / mass;
	}

	void ApplyForce(const glm::vec2& force);
	void Step(float dt);
	void Draw(class Graphics* m_graphics);
	bool Intersects(class Body* body);

	void ClearForce() { force = glm::vec2{ 0, 0 }; }

public:
	class Shape* shape{ nullptr };

	Type type = DYNAMIC;

	glm::vec2 position{ 0, 0 };
	glm::vec2 velocity{ 0, 0 };
	glm::vec2 force{ 0, 0 };

	float gravityScale{ 1 };
	float mass{ 1 };
	float invMass{ 1 };
	float damping{ 3 };

	float restitution{ 0.3f };
};