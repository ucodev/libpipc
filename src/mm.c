/**
 * @file mm.c
 * @brief Potable IPC Library (libpipc)
 *        Memory Management interface
 *
 * Date: 29-04-2015
 * 
 * Copyright 2015 Pedro A. Hortas (pah@ucodev.org)
 *
 * This file is part of libpipc.
 *
 * libpipc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libpipc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpipc.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdlib.h>

#include "config.h"

#ifdef USE_LIBFSMA
 #include <fsma/fsma.h>
#endif

void *mm_alloc(size_t size) {
	return
#ifdef USE_LIBFSMA
	fsma_malloc(size);
#else
	malloc(size);
#endif
}

void mm_free(void *ptr) {
#ifdef USE_LIBFSMA
	fsma_free(ptr);
#else
	free(ptr);
#endif
}

void *mm_realloc(void *ptr, size_t size) {
	return
#ifdef USE_LIBFSMA
	fsma_realloc(ptr, size);
#else
	realloc(ptr, size);
#endif
}

void *mm_calloc(size_t nmemb, size_t size) {
	return
#ifdef USE_LIBFSMA
	fsma_calloc(nmemb, size);
#else
	calloc(nmemb, size);
#endif
}

