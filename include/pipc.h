/**
 * @file pipc.h
 * @brief Portable IPC Library
 *        Public Library interface header
 *
 * Date: 13-05-2015
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

#ifndef LIBPIPC_PIPC_H
#define LIBPIPC_PIPC_H

#include <stdio.h>

#include <sys/types.h>

/* Types */
typedef unsigned short pipck_t;

/* Structures */
typedef struct pipcd_struct {
	int d;		/* IPC descriptor */
	pipck_t key;
	size_t msgmax;
	size_t msgsize;
	mode_t mode;
} pipcd_t;

/* Prototypes */
pipcd_t *pipc_master_register(pipck_t key, long id, size_t msgmax, size_t msgsize, uid_t uid, gid_t gid, mode_t mode);
pipcd_t *pipc_slave_register(pipck_t key, long id, size_t msgmax, size_t msgsize, mode_t mode);
ssize_t pipc_send(pipcd_t *pipcd, long src_id, long dst_id, const char *msg, size_t count);
ssize_t pipc_recv(pipcd_t *pipcd, long *src_id, long *dst_id, char *msg, size_t count);
ssize_t pipc_send_nowait(pipcd_t *pipcd, long src_id, long dst_id, const char *msg, size_t count);
ssize_t pipc_recv_nowait(pipcd_t *pipcd, long *src_id, long *dst_id, char *msg, size_t count);
int pipc_master_unregister(pipcd_t *pipcd);
int pipc_slave_unregister(pipcd_t *pipcd);
int pipc_pending(pipcd_t *pipcd);

#endif

