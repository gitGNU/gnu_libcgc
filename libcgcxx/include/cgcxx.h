/* 
 * File:   gc.h
 * Author: ethan
 *
 * Created on February 21, 2015, 3:49 PM
 */

#ifndef GC_H
#define	GC_H

#include <cstdio>
#include <typeinfo>
#include <cxxabi.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <typeindex>
#include <stdexcept>

class gc_container;
template<typename T> class gc_ptr;


/**
 *
 */
struct gc_entry
{
    gc_container* container;
};

/**
 * 
 */
class gc
{
public:
    
    /**
     * 
     */
    static void init();
    
    /**
     * 
     */
    template<typename _Tp1>
    static void push(gc_container* _ptr)
    {
        gc_ptr<_Tp1>* ptr = static_cast<gc_ptr<_Tp1>*>(_ptr);
    
        int i;
        
        gc_entry* entry = new gc_entry 
        { 
            .container = ptr
        };
        
        //printf("Address of new gc_ptr<%s> is %p\n", abi::__cxa_demangle(typeid(_Tp1).name(), 0, 0, &i), (void*) ptr->ptr()); 
        
        gc::_S_ptrs.push_back(entry);
        
    }
    
    /**
     * 
     */
    static void cleanup(bool force = false);
    
private:
    
    /**
     * 
     */
    gc();
    
    /**
     * 
     */
    gc(const gc& orig);
    
    /**
     * 
     */
    virtual ~gc();
    
    /**
     *
     */
    static std::vector<gc_entry*> _S_ptrs;
    
    static bool loaded;
};

class gc_container
{
};

template<typename _Tp1>
class gc_ptr : public gc_container
{
public:
    
    gc_ptr(_Tp1* ptr) : _M_ptr(ptr), _M_done(false)
    {
        gc::push<_Tp1* >(this);
    }
    
    ~gc_ptr()
    {
        delete _M_ptr;
    }
    
    _Tp1* ptr()
    {
        return this->_M_ptr;
    }
    
    _Tp1& ref()
    {
        if (this->is_done())
        {
            throw std::runtime_error("The object pointed to by gc_ptr<T> has been deallocated.");
        }
        return *this->_M_ptr;
    }
    
    _Tp1* operator-> ()
    {
        return this->ptr();
    }
    
    _Tp1& operator* ()
    {
        return this->ref();
    }
    
    void done(bool done = true)
    {
        this->_M_done = done;
    }
    
    bool is_done()
    {
        return this->_M_done;
    }
    
    void force_delete()
    {
        this->done();
        delete this->_M_ptr;
        this->_M_ptr = NULL;
    }
private:
    /**
     *
     */
    _Tp1* _M_ptr;
    
    /**
     * 
     */
    bool _M_done; 
};

void __gc_cleanup(void);

#endif	/* GC_H */