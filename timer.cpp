//
// Created by Vladimir Yarotsky on 1/2/17.
//

#include "timer.h"

Timer::Timer() {
    m_startTicks = 0;
    m_pausedTicks = 0;
    m_started = false;
    m_paused = false;
}

Timer::~Timer() {
}

void Timer::Start() {
    m_started = true;
    m_paused = false;

    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
}

void Timer::Stop() {
    m_started = false;
    m_paused = false;

    m_startTicks = 0;
    m_pausedTicks = 0;
}

void Timer::Pause() {
    if (!m_started || (m_started && m_paused)) {
        return;
    }

    m_paused = true;

    m_pausedTicks = SDL_GetTicks() - m_startTicks;
    m_startTicks = 0;
}

void Timer::Unpause() {
    if (!m_paused) {
        return;
    }
    m_paused = false;
    m_startTicks = SDL_GetTicks() - m_pausedTicks;
    m_pausedTicks = 0;
}

Uint32 Timer::GetTicks() {
    Uint32 time = 0;

    if (!m_started) {
        return 0;
    }
    return m_paused ? m_pausedTicks : SDL_GetTicks() - m_startTicks;
}

bool Timer::IsStarted() {
    return m_started;
}

bool Timer::IsPaused() {
    return m_paused;
}

