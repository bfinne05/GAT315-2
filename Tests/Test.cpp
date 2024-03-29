#include "Test.h"

Test::Test()
{
	//
}

Test::~Test()
{
	if (m_world) delete m_world;
	if (m_time) delete m_time;
	if (m_input) delete m_input;
	if (m_graphics) delete m_graphics;
}

void Test::Initialize()
{
	m_graphics = new Graphics();
	m_graphics->CreateWindow("Physics", 800, 600, 50); //fix size later
	m_world = new World();
	m_input = new Input();
	m_time = new Time2();
	m_time->SetFixedDeltaTime(1 / 60.0f);
}

void Test::Run()
{
	// Update
	Update();
	m_fixedTime += m_time->TimeDelta();
	while (m_fixedTime >= m_time->GetFixedDeltaTime())
	{
		FixedUpdate();
		m_fixedTime -= m_time->GetFixedDeltaTime();
	}

	// Render
	PreRender();
	Render();
	PostRender();
}

void Test::Update()
{
	UpdateEvents();

	m_input->Update();
	m_time->Update();
}

void Test::PreRender()
{
	m_graphics->SetColor({ 0, 0, 0, 0 });
	m_graphics->Clear();
}

void Test::PostRender()
{
	m_graphics->Present();
}

void Test::UpdateEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_quit = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_quit = true;
		}
	}
}
