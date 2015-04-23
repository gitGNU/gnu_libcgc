/* 
 * File:   gc.cpp
 * Author: ethan
 * 
 * Created on February 21, 2015, 3:49 PM
 */

#include <cstdlib>
#include <cstdio>
#include "cgcxx.h"

/**
 * 
 */
std::vector<gc_entry*> gc::_S_ptrs;

/**
 * 
 */
bool gc::loaded = false;

/**
 * 
 */
void gc::init()
{
    if (!gc::loaded)
    {
        std::atexit(__gc_cleanup);
        gc::loaded = true;
    }
}

/**
 * 
 */
void gc::cleanup(bool force)
{
    for(int i = 0; i < gc::_S_ptrs.size(); i++)
    {
        gc_entry* entry = gc::_S_ptrs.at(i);
        if (((gc_ptr<std::size_t>*) entry->container)->is_done() || force)
        {
            delete entry;
            gc::_S_ptrs.erase(gc::_S_ptrs.begin() + i);
        }
    }
}


/**
 * 
 */
gc::gc()
{
    
}

/**
 * 
 */
gc::gc(const gc& orig)
{
    
}

/**
 * 
 */
gc::~gc()
{
    
}


/**
 *
 */
void __gc_cleanup(void)
{
    gc::cleanup(true);
}
