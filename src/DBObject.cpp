#include "DBObject.h"

bool CDBObject::Init() {
    if(mysql_init(&m_SqlConn) == nullptr){
        return false;
    }

    return true;
}

void CDBObject::Dispose() {
    mysql_close(&m_SqlConn);
}
