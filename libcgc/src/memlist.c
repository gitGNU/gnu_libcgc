/* memlist.c - Implementation of the LibCGC memory */

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

#include <memlist.h>
#include <stdlib.h>
#include <string.h>

cgc_memlist_t cgc_memory_list;

void cgc_memlist_add(void* ptr, size_t size) {
	cgc_memlist_element_t* new_element = create_new_list_element(ptr, size);

	if (cgc_memory_list.root == NULL) {
		cgc_memory_list.root = new_element;
	} else {

		/* Find next open slot */
		cgc_memlist_element_t* current_element = cgc_memory_list.root; 
		while(1) {
			if (current_element->next == NULL) {
				current_element->next = new_element;
			}
		} 
	}
}

cgc_memlist_element_t* create_new_list_element(void* ptr, size_t size) {
	cgc_memlist_element_t* new_element = (cgc_memlist_element_t*) malloc(sizeof(cgc_memlist_element_t));
	memset(new_element, '\0', sizeof(cgc_memlist_element_t));
	
	new_element->ptr = ptr;
	new_element->size = size;
	
	return new_element;
}

void cgc_memlist_init() {
	cgc_memory_list.root = NULL;
}
