#include "GlobalDBObject.h"


bool CGlobalDBObject::Init() {
    if( CDBObject::Init() == false ){
        return false;
    }

    MYSQL* ptr_connection = mysql_real_connect(&m_SqlConn, "172.16.254.5", "root", "root", "JHNet", 9876, (char*)NULL, 0 );
    if(ptr_connection == nullptr){
        return false;
    }

    return true;
}