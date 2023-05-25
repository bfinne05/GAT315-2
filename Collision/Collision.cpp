#include "Collision.h"
#include "../Engine/CircleShape.h"
#include "Random.h"
namespace Collision
{
    void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts)
    {
        if (bodies.empty()) return;

        for (size_t i = 0; i < bodies.size() - 1; i++)
        {
            for (size_t j = i + 1; j < bodies.size(); j++)
            {
                Body* bodyA = bodies[i];
                Body* bodyB = bodies[j];

                // contact needs at least one dynamic body
                if (bodyA->type != Body::DYNAMIC && bodyB->type != Body::DYNAMIC) continue;

                // check for intersection between bodies
                if (bodyA->Intersects(bodyB))
                {
                    // create contact
                    Contact contact = Collision::GenerateContact(bodyA, bodyB);
                    contacts.push_back(contact);
                }
            }
        }
    }

    Contact GenerateContact(Body* bodyA, Body* bodyB)
    {
        Contact contact;

        contact.BodyA = bodyA;
        contact.BodyB = bodyB;

        glm::vec2 direction = bodyA->position - bodyB->position;
        float distance = glm::length(direction);
        if (distance == 0)
        {
            direction = { randomf(-0.05, 0.05f), randomf(-0.05, 0.05f) };
        }

        float radius = ((CircleShape*)bodyA->shape)->radius + ((CircleShape*)bodyB->shape)->radius;
        contact.depth = radius - distance;

        contact.normal = glm::normalize(direction); 

        contact.restitution = (bodyA->restitution + bodyB->restitution) * 0.5f;

        return contact;
    }
    void SeperateContacts(std::vector<Contact>& contacts)
    {
        for (auto& contact : contacts)
        {
            float totalInverseMass = contact.BodyA->invMass + contact.BodyB->invMass;
            glm::vec2 seperation = contact.normal * (contact.depth / totalInverseMass);

            contact.BodyA->position += seperation * contact.BodyA->invMass;
            contact.BodyB->position -= seperation * contact.BodyB->invMass;
        }
    }

    void ResolveContacts(std::vector<Contact>& contacts)
    {
        for (auto& contact : contacts)
        {
            glm::vec2 relativeVelocity = contact.BodyA->velocity - contact.BodyB->velocity;
            float normalVelocity = glm::dot(relativeVelocity, contact.normal);
            if (normalVelocity > 0.0) continue;

            float totalINVMass = contact.BodyA->invMass + contact.BodyB->invMass;
            float impulseMagnitude = -(1.0f + contact.restitution) * normalVelocity * totalINVMass;

            glm::vec2 impulse = contact.normal * impulseMagnitude;

            contact.BodyA->velocity += (impulse * contact.BodyA->invMass);
            contact.BodyB->velocity -= (impulse * contact.BodyB->invMass);
        }
    }
}
