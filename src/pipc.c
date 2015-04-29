/**
 * @file pipc.c
 * @brief Potable IPC Library (libpipc)
 *        Public Library interface
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


#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "pipc.h"
#include "mm.h"

static pipcd_t *_pipc_create(
	pipck_t key,
	long id,
	size_t msgmax,
	size_t msgsize,
	mode_t mode,
	int flags)
{
	int errsv = 0;
	pipcd_t *pipcd = NULL;

	/* Allocate IPC descriptor structure */
	if (!(pipcd = mm_alloc(sizeof(pipcd_t))))
		return NULL;

	/* Create the IPC engine */
	if ((pipcd->d = msgget((key_t) key, flags | mode)) < 0) {
		errsv = errno;
		mm_free(pipcd);
		errno = errsv;
		return NULL;
	}

	/* Set the IPC parameters */
	pipcd->key = key;
	pipcd->msgmax = msgmax;
	pipcd->msgsize = msgsize;
	pipcd->mode = mode;

	/* All good */
	return pipcd;
}

pipcd_t *pipc_master_register(pipck_t key, long id, size_t msgmax, size_t msgsize, mode_t mode) {
	return _pipc_create(key, id, msgmax, msgsize, mode, IPC_CREAT);
}

pipcd_t *pipc_slave_register(pipck_t key, long id, size_t msgmax, size_t msgsize, mode_t mode) {
	return _pipc_create(key, id, msgmax, msgsize, mode, 0);
}

int pipc_send(pipcd_t *pipcd, long src_id, long dst_id, const char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_recv(pipcd_t *pipcd, long *src_id, char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_send_nowait(pipcd_t *pipcd, long src_id, long dst_id, const char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_recv_nowait(pipcd_t *pipcd, long *src_id, char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_master_unregister(pipcd_t *pipcd) {
	errno = ENOSYS;
	return -1;
}

int pipc_slave_unregister(pipcd_t *pipcd) {
	errno = ENOSYS;
	return -1;
}

