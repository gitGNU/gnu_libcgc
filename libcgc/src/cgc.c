/* gcg.c - LibCGC main implementation */

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

#include <cgc.h>
#include <memlist.h>

void cgc_init() {
	cgc_memlist_init();
	atexit(cgc_cleanup);
}

void cgc_cleanup() {
	cgc_memlist_element_t* node = cgc_memory_list.root;
	
	while(node != NULL) {
		cgc_memlist_element_t* tmp = node;
		node = node->next;
		cgc_free_element(tmp);
		free(tmp);	
	}
	cgc_memory_list.root = NULL;
}

void cgc_free_element(cgc_memlist_element_t* element) {
	free(element->ptr);
	element->ptr = NULL;
	element->size = 0;
}