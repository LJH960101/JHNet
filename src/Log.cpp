#include "Log.h"
#include <fstream>
using namespace std;

IMPLEMENT_SINGLETON(CLog);

void CLog::_Tick() {
    if(_SwapQueue() == false){
        return;
    }

    ofstream file(m_logPath.data(), fstream::out | fstream::app);
    if(!file.is_open()){
        return;
    }

    for( string log : *m_lstLogCurrent ){
        file << log << endl;
    }

    file.close();

    m_lstLogCurrent->clear();
}

CLog::CLog() {
    m_lstLogReserved = new list<string>();
    m_lstLogCurrent = new list<string>();
}

CLog::~CLog() {
    delete m_lstLogReserved;
    delete m_lstLogCurrent;
}

bool CLog::_SwapQueue() {
    lock_guard locker(m_mtxList);

    if(m_lstLogReserved->empty() == true){
        return false;
    }

    swap(m_lstLogReserved, m_lstLogCurrent);
    return true;
}

bool CLog::Init(const string& logPath) {
    m_logPath = logPath;

    return Begin();
}

void CLog::PushLog(const std::string& log) {
    lock_guard locker(m_mtxList);
    m_lstLogReserved->push_back(log);
}