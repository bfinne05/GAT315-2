#include "ForceTest.h"
#include "GravitationalGenerator.h"
#include "DragForce.h"
#include "AreaForce.h"
#include "PointForce.h"
#include "CircleShape.h"

//#define POINT_FORCE
//#define AREA_FORCE
#define DRAG_FORCE
void ForceTest::Initialize()
{
    Test::Initialize();

    //auto forceGenerator = new GravitationalGenerator(400);
    //m_world->AddForceGenerator(forceGenerator);
#if defined(POINT_FORCE)
    auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
    ForceGenerator* forceGenerator = new PointForce(body, 2000);
    m_world->AddForceGenerator(forceGenerator);
#elif defined(AREA_FORCE)
    auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
    ForceGenerator* forceGenerator = new AreaForce(body, 2000, -90);
    m_world->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
    auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
    ForceGenerator* forceGenerator = new DragForce(body, 0.5f);
    m_world->AddForceGenerator(forceGenerator);
#endif
}

void ForceTest::Update()
{
    glm::vec2 position = m_graphics->ScreenToWorld(m_input->GetMousePosition());

    Test::Update();

    if (m_input->GetMouseButton(0))
    {
        glm::vec2 velocity = randomUnitCircle() * randomf(1, 2);

        float size = randomf(0.1f, 1);
        glm::vec4 color{ randomf(), randomf(), randomf(), 1 };
        auto body = new Body(new CircleShape(size, color), position, velocity, size);
        body->damping = 1;
        body->gravityScale = 0;
        m_world->AddBody(body);
    }
}

void ForceTest::FixedUpdate()
{
    m_world->Step(m_time->GetFixedDeltaTime());
}

void ForceTest::Render()
{
    m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
    m_world->Draw(m_graphics);
}
