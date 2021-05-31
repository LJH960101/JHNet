#pragma once
#include "MacroHelper.h"
class CRTTI{
public:
    CRTTI( const char* name, const CRTTI& parent ) : m_name(name), m_parent(parent) {}
    const char* GetType(){
        return m_name;
    }
private:
    const char* m_name;
    const CRTTI& m_parent;
};

#define DEFINE_RTTI(CLASS_NAME) \
public:\
    static CRTTI m_rtti;\
    static const char* GetType(){ return m_rtti.GetType(); }

#define IMPLEMENT_RTTI(...)    OVERLOADED_MACRO(IMPLEMENT_RTTI, __VA_ARGS__)

#define IMPLEMENT_RTTI1(CLASS_NAME)\
    CRTTI CLASS_NAME::m_rtti(#CLASS_NAME, CLASS_NAME::m_rtti)

#define IMPLEMENT_RTTI2(CLASS_NAME, PARENT_CLASS)\
    CRTTI CLASS_NAME::m_rtti(#CLASS_NAME, PARENT_CLASS::m_rtti)