#pragma once
#include "ForceGenerator.h"
class AreaForce : public ForceGenerator
{
public:
	AreaForce(Body* body, float forceMagnitude, float angle) : //<take in the pointer to a body, force magnitudeand angle>) :
		ForceGenerator{body},
		m_forceMagnitude{forceMagnitude},
		m_angle{angle}
	{}
	void Apply(std::vector<class Body*> bodies) override;
private:
	float m_forceMagnitude{ 1 };
	float m_angle{ 0 };
};