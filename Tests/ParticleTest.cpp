#include "ParticleTest.h"

void ParticleTest::Initialize()
{
    Test::Initialize();
}

void ParticleTest::Update()
{
    glm::vec2 position = m_graphics->ScreenToWorld(m_input->GetMousePosition());

    Test::Update();

    if (m_input->GetMouseButton(0))
    {
        glm::vec2 velocity = randomUnitCircle() * randomf(10, 20);
        glm::vec4 color{ randomf(), randomf(), randomf(), 1 };

        auto body = new Body(new CircleShape(randomf(1, 2), color), position, velocity);
        body->damping = 1;
        m_world->AddBody(body);
    }
}

void ParticleTest::FixedUpdate()
{
    m_world->Step(m_time->GetFixedDeltaTime());
}

void ParticleTest::Render()
{
    m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
    m_world->Draw(m_graphics);
}
