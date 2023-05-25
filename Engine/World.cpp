#include "World.h"
#include "Body.h"
#include "ForceGenerator.h"
#include "Joint.h"
#include "../Collision/Collision.h"
#include <vector>

glm::vec2 World::gravity{ 0, -9.8f };

World::~World()
{
	// <delete all the objects>
	for (auto body : m_bodies)
	{
		delete body;
	}

	// <clear the objects form the list clear()>
	m_bodies.clear();
}
void World::Step(float dt)
{
	for (auto joint : m_joints) joint->Step(dt);

	std::vector<Body*> bodies(m_bodies.begin(), m_bodies.end()); //check this out later if not working
	if (!m_bodies.empty() && !m_forceGenerators.empty())//<check that m_bodies is not empty and m_forceGenerators is not empty>)
	{
		for (auto forceGenerator : m_forceGenerators)
		{
			forceGenerator->Apply(bodies);
		}
	}

	for (auto body : m_bodies) body->Step(dt);
	//collision

	std::vector<Contact> contacts;
	Collision::CreateContacts(bodies, contacts);
	Collision::SeperateContacts(contacts);
	Collision::ResolveContacts(contacts);


}
void World::Draw(Graphics* graphics)
{
	for (auto joints : m_joints) joints->Draw(graphics);

	for (auto forceGenerator : m_forceGenerators)
	{
		forceGenerator->Draw(graphics);
	}
	for (auto body : m_bodies)
	{
		body->Draw(graphics);
	}
}
void World::AddBody(Body* body)
{
	// <push back the po onto objects list>
	m_bodies.push_back(body);
}
void World::RemoveBody(Body* body)
{
	// <remove po from the objects list>
	m_bodies.remove(body);
}

void World::AddJoint(Joint* joint)
{
	m_joints.push_back(joint);
}

void World::RemoveJoint(Joint* joint)
{
	m_joints.remove(joint);
}

void World::AddForceGenerator(ForceGenerator* forceGenerator)
{
	m_forceGenerators.push_back(forceGenerator);
}
