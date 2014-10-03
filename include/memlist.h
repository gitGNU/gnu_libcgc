/* memlist.h - Implementation of the LibCGC memory list header */

/* Copyright (C) 2014 Ethan Sattler

   This file is part of LibCGC, the C Garbage Collector

   LibCGC is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser Public License as published by
   the Free Software Foundation, either version 2.1 of the License, or
   (at your option) any later version.

   LibCGC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU Lesser Public License
   along with LibCGC.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MEMLIST_H
#define MEMLIST_H

#include <stdlib.h>

/**
*
*/
typedef struct cgc_memlist_element {
	void* ptr;
	size_t size;
	struct cgc_memlist_element* next;
} cgc_memlist_element_t;

/**
*
*/
typedef struct cgc_memlist {
	cgc_memlist_element_t* root;
} cgc_memlist_t;

/**
*
*/
extern cgc_memlist_t cgc_memory_list;

/**
*
*/
void cgc_memlist_add(void* ptr, size_t size);

/**
*
*/
cgc_memlist_element_t* create_new_list_element(void* ptr, size_t size);

/**
*
*/
void cgc_memlist_init();

#endif