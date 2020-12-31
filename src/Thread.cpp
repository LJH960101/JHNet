#include "Thread.h"
#include <chrono>

CThread::CThread() : m_bTerminated(true), m_bRunning(false) {}
CThread::~CThread(){
    End();
}

bool CThread::Begin(){
    if(m_bTerminated == false){
        return false;
    }

    m_bTerminated = false;
    m_bRunning = true;
    m_thread = std::thread { &CThread::_ThreadProc, this };

    return true;
}

void CThread::End(){
    if(m_bTerminated == true){
        return ;
    }

    m_bRunning = false;
    while(!m_bTerminated){
        std::this_thread::yield();
    }
}

void CThread::_ThreadProc(){
    while(m_bRunning){
        _Tick();
    }
    m_bTerminated = true;
}