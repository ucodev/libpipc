/**
 * @file pipc.h
 * @brief Portable IPC Library
 *        Public Library interface header
 *
 * Date: 27-04-2015
 * 
 * Copyright 2015 Pedro A. Hortas (pah@ucodev.org)
 *
 * This file is part of usched.
 *
 * usched is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * usched is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with usched.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LIBPIPC_PIPC_H
#define LIBPIPC_PIPC_H

/* Prototypes */
int pipc_register(
	const char *name,
	const char *key,
	long id,
	size_t msgmax,
	size_t msgsize,
	int flags);
int pipc_send(int pipcd, long src_id, long dst_id, const char *msg, size_t count);
int pipc_recv(int pipcd, long id, char *msg, size_t count);
int pipc_timedsend(
	int pipcd,
	long src_id,
	long dst_id,
	const char *msg,
	size_t count,
	const struct timespec *timeout);
int pipc_timedrecv(int pipcd, long id, char *msg, size_t count, const struct timespec *timeout);
int pipc_unregister(int pipcd);
int pipc_unlink(const char *name);

#endif

