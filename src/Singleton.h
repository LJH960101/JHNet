#pragma once

#define DEFINE_SINGLETON(TClass) \
    protected:\
    static TClass* m_instance;\
    public:\
    static TClass* GetInstance()

#define IMPLEMENT_SINGLETON(TClass) \
    TClass* TClass::m_instance = nullptr;\
    TClass* TClass::GetInstance(){\
            if(m_instance == nullptr){\
                m_instance = new TClass();\
            }\
            return m_instance;\
    }