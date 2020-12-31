#pragma once
#include <mutex>

class CLocker{
public:
    CLocker( std::mutex& mutex ) : m_mutex(mutex){
        mutex.lock();
    }
    ~CLocker(){
        m_mutex.unlock();
    }

private:
    std::mutex& m_mutex;
};