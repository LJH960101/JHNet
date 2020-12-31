#pragma once
#include "ObjectPool.h"
#include <mysql/mysql.h>

class CDBObject : public IReusable{
public:
    virtual bool Init() override;
    virtual void Dispose() override;

protected:
    MYSQL m_SqlConn;
};