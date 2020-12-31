#pragma once
#include <thread>

class CThread{
public:
    CThread();
    ~CThread();
    bool Begin();
    void End(); 

protected:
    virtual void _Tick() = 0;

private:
    void _ThreadProc();

    std::thread m_thread;
    volatile bool m_bRunning;
    volatile bool m_bTerminated;
};