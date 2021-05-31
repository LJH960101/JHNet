#pragma once
#include "ObjectPool.h"
#include <mysql/mysql.h>

class CDBObject {
public:
    CDBObject();
    ~CDBObject();

protected:
    MYSQL m_SqlConn;
};