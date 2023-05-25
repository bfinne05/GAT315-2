#pragma once
#include "Graphics.h"
#include "Input.h"
#include "Time2.h"
#include "Random.h"
#include "World.h"

class Test
{
public:
	Test();
	~Test();

	virtual void Initialize();
	virtual void Run();

	virtual void Update();
	virtual void FixedUpdate() = 0;

	virtual void PreRender();
	virtual void Render() = 0;
	virtual void PostRender();

	bool IsQuit() { return m_quit; }

protected:
	void UpdateEvents();

protected:
	bool m_quit{ false };
	float m_fixedTime{ 0 };

	class World* m_world{ nullptr };
	class Graphics* m_graphics{ nullptr };
	class Input* m_input{ nullptr };
	class Time2* m_time{ nullptr };
};
