#pragma once
#include "Contact.h"
#include "../Engine/Body.h"
#include <vector>
namespace Collision
{
	void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts);
	Contact GenerateContact(Body* bodyA, Body* bodyB);

	void SeperateContacts(std::vector<Contact>& contacts);
	void ResolveContacts(std::vector<Contact>& contacts);
	
}