#pragma once
#include <tbb/concurrent_queue.h>
#include <type_traits>
 
class IReusable{
public:
    virtual bool Init() = 0;
    virtual void Dispose() = 0;
};
 
template<typename T>
class CObjectPool{
    static_assert(std::is_base_of<IReusable, T>::value, "T must inherit from IReusable");
    
public:
    CObjectPool(int size = 100){
        _maxSize = size;
        
        for (int i = 0; i < _maxSize; ++i) {
            T* newObject = new T();
            _qObjects.push(newObject);
        }
    }
    
    ~CObjectPool()
    {
        while (!_qObjects.empty()) {
            T* object;
            if( _qObjects.try_pop( object ) == true ){
                delete object;
            }
        }
 
        _maxSize = 0;
    }
    
    // 오브젝트를 꺼낸다.
    T* PopObject()
    {
        T* retVal;
        
        // 꺼낼게 없으면 하나 걍 만들자.
        if( _qObjects.try_pop(retVal) == false ){
            retVal = new T();
            ++_maxSize;
        }
        
        if( retVal->Init() == false ){
            return nullptr;
        }
 
        return retVal;
    }
    
    // 오브젝트를 수거한다.
    void ReturnObject(T* object)
    {
        object->Dispose();
        _qObjects.push(object);
    }
    
private:
    tbb::concurrent_queue<T*> _qObjects;
    int _maxSize; // 최대 배열 크기 (누수 체크나 모니터링 용도로 사용하면 좋을듯)
};