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
#include <string.h>
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
	struct msqid_ds qctl;

	memset(&qctl, 0, sizeof(struct msqid_ds));

	/* Allocate IPC descriptor structure */
	if (!(pipcd = mm_alloc(sizeof(pipcd_t))))
		return NULL;

	/* Reset descriptor memory */
	memset(pipcd, 0, sizeof(pipcd_t));

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

	/* Get IPC properties */
	if (msgctl(pipcd->d, IPC_STAT, &qctl) < 0) {
		errsv = errno;
		mm_free(pipcd);
		errno = errsv;
		return NULL;
	}

	/* Change the queue size */
	qctl.msg_qbytes = msgmax * msgsize;

	/* Set the new queue size */
	if (msgctl(pipcd->d, IPC_SET, &qctl) < 0) {
		errsv = errno;
		mm_free(pipcd);
		errno = errsv;
		return NULL;
	}

	/* All good */
	return pipcd;
}

pipcd_t *pipc_master_register(pipck_t key, long id, size_t msgmax, size_t msgsize, mode_t mode) {
	return _pipc_create(key, id, msgmax, msgsize, mode, IPC_CREAT);
}

pipcd_t *pipc_slave_register(pipck_t key, long id, size_t msgmax, size_t msgsize, mode_t mode) {
	return _pipc_create(key, id, msgmax, msgsize, mode, 0);
}

static ssize_t _pipc_generic_send(
	pipcd_t *pipcd,
	long src_id,
	long dst_id,
	const char *msg,
	size_t count,
	int flags)
{
	int errsv = 0;
	char *buf = NULL;

	/* Allocate transmission buffer */
	if (!(buf = mm_alloc((sizeof(long) * 2) + count)))
		return -1;

	/* Craft transmission buffer */
	memcpy(buf, &dst_id, sizeof(long));
	memcpy(buf + sizeof(long), &src_id, sizeof(long));
	memcpy(buf + (sizeof(long) * 2), msg, count);

	/* Send message */
	if (msgsnd(pipcd->d, buf, sizeof(long) + count, flags) < 0) {
		errsv = errno;
		mm_free(buf);
		errno = errsv;
		return -1;
	}

	/* Reset buffer memory */
	memset(buf, 0, (sizeof(long) * 2) + count);

	/* Free buffer memory */
	mm_free(buf);

	/* All good */
	return count;
}

static ssize_t _pipc_generic_recv(
	pipcd_t *pipcd,
	long *src_id,
	long *dst_id,
	char *msg,
	size_t count,
	int flags)
{
	int errsv = 0;
	char *buf = NULL;
	ssize_t count_ret = 0;

	/* Allocate transmission buffer */
	if (!(buf = mm_alloc((sizeof(long) * 2) + count)))
		return -1;

	/* Receive message */
	if ((count_ret = msgrcv(pipcd->d, buf, sizeof(long) + count, *dst_id, flags)) < 0) {
		errsv = errno;
		mm_free(buf);
		errno = errsv;
		return -1;
	}

	/* Set message type */
	memcpy(dst_id, buf, sizeof(long));
	memcpy(src_id, buf + sizeof(long), sizeof(long));
	memcpy(msg, buf + (sizeof(long) * 2), count_ret);

	/* Reset buffer memory */
	memset(buf, 0, (sizeof(long) * 2) + count);

	/* Free buffer memory */
	mm_free(buf);

	/* All good */
	return count_ret - sizeof(long);
}

ssize_t pipc_send(pipcd_t *pipcd, long src_id, long dst_id, const char *msg, size_t count) {
	return _pipc_generic_send(pipcd, src_id, dst_id, msg, count, MSG_NOERROR);
}

ssize_t pipc_recv(pipcd_t *pipcd, long *src_id, long *dst_id, char *msg, size_t count) {
	return _pipc_generic_recv(pipcd, src_id, dst_id, msg, count, MSG_NOERROR);
}

ssize_t pipc_send_nowait(pipcd_t *pipcd, long src_id, long dst_id, const char *msg, size_t count) {
	return _pipc_generic_send(pipcd, src_id, dst_id, msg, count, MSG_NOERROR | IPC_NOWAIT);
}

ssize_t pipc_recv_nowait(pipcd_t *pipcd, long *src_id, long *dst_id, char *msg, size_t count) {
	return _pipc_generic_recv(pipcd, src_id, dst_id, msg, count, MSG_NOERROR | IPC_NOWAIT);
}

int pipc_master_unregister(pipcd_t *pipcd) {
	struct msqid_ds qctl;

	/* Reset IPC message queue structure */
	memset(&qctl, 0, sizeof(struct msqid_ds));

	/* Get IPC properties */
	if (msgctl(pipcd->d, IPC_STAT, &qctl) < 0)
		return -1;

	/* Remove the IPC descriptor */
	if (msgctl(pipcd->d, IPC_RMID, &qctl) < 0)
		return -1;

	/* Reset IPC descriptor structure memory */
	memset(pipcd, 0, sizeof(pipcd_t));

	/* Free IPC descriptor structure memory */
	mm_free(pipcd);

	/* All good */
	return 0;
}

int pipc_slave_unregister(pipcd_t *pipcd) {
	/* Reset IPC descriptor structure memory */
	memset(pipcd, 0, sizeof(pipcd_t));

	/* Free IPC descriptor structure memory */
	mm_free(pipcd);

	/* All good */
	return 0;
}

int pipc_pending(pipcd_t *pipcd) {
	struct msqid_ds qctl;

	/* Reset IPC message queue structure */
	memset(&qctl, 0, sizeof(struct msqid_ds));

	/* Get IPC properties */
	if (msgctl(pipcd->d, IPC_STAT, &qctl) < 0)
		return -1;

	/* Return the number of messages in queue */
	return qctl.msg_qnum;
}

