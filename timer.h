//
// Created by Vladimir Yarotsky on 1/2/17.
//

#ifndef SDL1_TIMER_H
#define SDL1_TIMER_H

#include <SDL.h>

class Timer {
public:
    Timer();
    ~Timer();

    void Start();
    void Stop();
    void Pause();
    void Unpause();
    Uint32 GetTicks();
    bool IsStarted();
    bool IsPaused();

private:
    Uint32 m_startTicks;
    Uint32 m_pausedTicks;
    bool m_started;
    bool m_paused;
};

#endif //SDL1_TIMER_H
