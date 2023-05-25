#include "JointTest.h"
#include "CircleShape.h"
#include "World.h"
#include "Body.h"
#include "Joint.h"

#define SPRING_STIFFNESS 100
#define SPRING_LENGTH 9
#define BODY_DAMPING 50
#define CHAIN_SIZE 3

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(1, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);
	
	auto prevBody = m_anchor;
	Body* AnchorA = m_anchor;
	Body* AnchorB = m_anchor;

	for (int i = 0; i < CHAIN_SIZE; i++)
	{
		//creates new body and places in the wold
		auto bodyA = new Body(new CircleShape(0.5, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::DYNAMIC);
		//bodyA->gravityScale = 250;
		bodyA->damping = BODY_DAMPING;
		m_world->AddBody(bodyA);

		//create right node
		auto bodyB = new Body(new CircleShape(0.5, { 1, 1, 1, 1 }), { 49, 20 }, { 0, 0 }, 1, Body::DYNAMIC);
		//bodyB->gravityScale = 250;
		bodyB->damping = BODY_DAMPING;
		m_world->AddBody(bodyB);

		//add two bodys too the anchor on the first loop
		auto joint = new Joint(AnchorA, bodyA, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);
		
		auto jointL = new Joint(AnchorB, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(jointL);

		auto joint1 = new Joint(bodyA, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint1);

		//create joint to new body
		auto joint2 = new Joint(AnchorA, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint2);

		auto joint3 = new Joint(AnchorB, bodyA, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint3);
		
		AnchorA = bodyA;
		AnchorB = bodyB;
	}

}

void JointTest::Update()
{
	Test::Update();
	m_anchor->position =  m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}