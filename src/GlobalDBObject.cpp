#include "GlobalDBObject.h"

CGlobalDBObject::CGlobalDBObject() : CDBObject() {
    MYSQL* ptr_connection = mysql_real_connect(&m_SqlConn, "172.16.254.5", "root", "root", "JHNet", 9876, (char*)NULL, 0 );
}