#pragma once
#include "Thread.h"
#include "Singleton.h"
#include <mutex>
#include <list>
#include <string>

#define Log(DATA)\
    CLog::GetInstance()->PushLog( DATA )

class CLog : public CThread{
    DEFINE_SINGLETON(CLog);

public:
    CLog();
    ~CLog();
    bool Init( const std::string& logPath );
    void PushLog( const std::string& log );

private:
    virtual void _Tick() override;
    bool _SwapQueue();

    std::list<std::string>* m_lstLogReserved;
    std::list<std::string>* m_lstLogCurrent;

    std::mutex m_mtxList;

    std::string m_logPath;
};