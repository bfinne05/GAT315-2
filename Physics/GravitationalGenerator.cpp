#include "GravitationalGenerator.h"
#include "Body.h"

void GravitationalGenerator::Apply(std::vector<class Body*> bodies)
{
	for (size_t i = 0; i < bodies.size() - 1; i++)
	{
		for (size_t j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyA = bodies[i];
			Body* bodyB = bodies[j];
			// apply gravitational force
			glm::vec2 direction = bodyA->position - bodyB->position;
			float distance = glm::length(direction);
			if (distance == 0) continue;
			distance = glm::max(1.0f, distance);
			float force = 9.81 * ((bodyA->mass * bodyB->mass) / distance); //use -9.81 if you want to go up
			glm::vec2 ndirection = glm::normalize(direction);
			bodyA->ApplyForce(-ndirection * force);
			bodyB->ApplyForce(ndirection * force);
		}
	}
}
