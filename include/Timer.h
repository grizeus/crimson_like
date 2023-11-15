#pragma once
#include <SDL.h>

class Timer {
public:
    Timer();
    ~Timer();

    void Start();
    void Stop();
    void Pause();
    void Unpause();

    Uint32 GetTicks() const;

    inline bool IsStarted() const { return m_Started; }
    inline bool IsPaused() const { return m_Paused; }
private:
    Uint32 m_StartTicks;
    Uint32 m_PausedTicks;
    bool m_Started;
    bool m_Paused;
};
