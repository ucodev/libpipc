#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

#include <sys/types.h>

#include "pipc.h"

pipcd_t pipc_create(const char *key, size_t msgmax, size_t msgsize, mode_t mode) {
	errno = ENOSYS;
	return -1;
}

pipcd_t pipc_register(const char *key, long id, mode_t mode) {
	errno = ENOSYS;
	return -1;
}

int pipc_send(pipcd_t pipcd, long src_id, long dst_id, const char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_recv(pipcd_t pipcd, long id, char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_send_nowait(pipcd_t pipcd, long src_id, long dst_id, const char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_recv_nowait(pipcd_t pipcd, long id, char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_unregister(pipcd_t pipcd) {
	errno = ENOSYS;
	return -1;
}

int pipc_destroy(pipcd_t pipcd) {
	errno = ENOSYS;
	return -1;
}

int pipc_unlink(const char *key) {
	errno = ENOSYS;
	return -1;
}

