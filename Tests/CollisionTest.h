#pragma once
#include "Test.h"
#include "CircleShape.h"
#include "World.h"
#include "Body.h"

class CollisionTest : public Test
{
public:
	void Initialize() override;

	void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render() override;

protected:
	class Body* m_user{ nullptr };
};
