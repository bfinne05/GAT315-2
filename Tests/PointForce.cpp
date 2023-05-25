#include "PointForce.h"
#include "Body.h"
#include "glm/glm.hpp"
void PointForce::Apply(std::vector<class Body*> bodies)
{
	for (auto body : bodies)
	{
		if (!m_body->Intersects(body)) continue;
		glm::vec2 direction = body->position - m_body->position;//<compute direction from body and m_body>
		glm::vec2 force = glm::normalize(direction);// <use the glm normalize from to create a unit vector>
		body->ApplyForce(force * m_forceMagnitude); //<scale the force with the force magnitude>);
	}
}
