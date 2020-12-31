#include "JHNet.h"
#include <iostream>
#include "Thread.h"
#include <chrono>
#include <thread>
#include <mysql/mysql.h>
#include "DBManager.h"
#include "Log.h"
#include <string>
using namespace std;

IMPLEMENT_SINGLETON(CJHNet);

class CThreadTest : public CThread
{
    public:
    CThreadTest() : CThread(){
        
    }

protected:
    virtual void _Tick() override {
        string log = to_string( CDBManager::GetInstance()->GetRowNumbs() );
        log = "DB Result : " + log;
        Log(log);
        std::this_thread::sleep_for( std::chrono::seconds(1) );
    }
};

void CJHNet::Start(){
    CLog::GetInstance()->Init( "logtest.log" );

    CThreadTest myThread;
    myThread.Begin();
    std::cout << "Start Thread !!\n";

    int a = 0;
    std::cin >> a;

    myThread.End();

    std::cin >> a;
    std::cout << "End Thread !!\n";
}