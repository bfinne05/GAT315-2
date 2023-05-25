#include "Time2.h"

Time2::Time2()
{
    m_prevTime = SDL_GetPerformanceCounter();
}

void Time2::Update()
{
    uint64_t m_time = SDL_GetPerformanceCounter();
    uint64_t elapsedTime = m_time - m_prevTime;
    m_prevTime = m_time;

    m_deltaTime = elapsedTime / (float)SDL_GetPerformanceFrequency();
    m_fps = 1 / m_deltaTime;
}

