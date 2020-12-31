#pragma once
#include "Singleton.h"

class CDBManager{
    DEFINE_SINGLETON(CDBManager);

public:
    CDBManager();
    int GetRowNumbs();
};