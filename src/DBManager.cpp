#include "DBManager.h"
#include <mysql/mysql.h>
#include <iostream>

IMPLEMENT_SINGLETON(CDBManager);

int CDBManager::GetRowNumbs() {
    MYSQL *connection = nullptr;
    MYSQL conn;
    MYSQL_RES *sql_result;
    MYSQL_ROW sql_row;
    int stat = 0;
    int retval = 0;

    if(mysql_init(&conn) == nullptr){
        std::cout << "mysql_init failed.\n";
        goto ErrProc;
    }

    connection = mysql_real_connect(&conn, "172.16.254.5", "root", "root", "GlobalDB", 9876, (char*)NULL, 0 );
    if(connection == NULL){
        std::cout << "Real connect failed. : " << mysql_error(&conn);
        goto ErrProc;
    }

    stat = mysql_query( connection, "Select * from KeyValueTest" );
    if(stat != 0){
        std::cout << "mysql_query failed. : " << mysql_error(&conn);
        goto ErrProc;
    }

    sql_result = mysql_store_result(connection);
    while((sql_row = mysql_fetch_row(sql_result)) != NULL)
    {
        ++retval;
        //printf("%s %s\n", sql_row[0], sql_row[1]);
    }

    mysql_close(connection);
    return retval;

    ErrProc:
    return 0;
}

CDBManager::CDBManager() {
    
}
