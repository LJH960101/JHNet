#include "JHNet.h"
#include <iostream>
#include "Thread.h"
#include <chrono>
#include <thread>
#include <mysql/mysql.h>
#include "DBManager.h"
#include "Log.h"
#include <string>

#include "SocketNetwork.h"
using namespace std;

IMPLEMENT_SINGLETON(CJHNet);

void CJHNet::Start(){
    if( CSocketNetwork::GetInstance()->Start( 11111 ) == false ){
        return;
    }

    int a;
    while(true){
        cin >> a;
        if(a==0){
            break;
        }
    }
    
    return;
}