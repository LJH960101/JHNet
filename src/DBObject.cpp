#include "DBObject.h"

CDBObject::CDBObject() {
    mysql_init(&m_SqlConn);
}

CDBObject::~CDBObject() {
    mysql_close(&m_SqlConn);
}