#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

int pipc_register(
	const char *name,
	const char *key,
	long id,
	size_t msgmax,
	size_t msgsize,
	int flags)
{
	errno = ENOSYS;
	return -1;
}

int pipc_send(int pipcd, long src_id, long dst_id, const char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_recv(int pipcd, long id, char *msg, size_t count) {
	errno = ENOSYS;
	return -1;
}

int pipc_timedsend(
	int pipcd,
	long src_id,
	long dst_id,
	const char *msg,
	size_t count,
	const struct timespec *timeout)
{
	errno = ENOSYS;
	return -1;
}

int pipc_timedrecv(int pipcd, long id, char *msg, size_t count, const struct timespec *timeout) {
	errno = ENOSYS;
	return -1;
}

int pipc_unregister(int pipcd) {
	errno = ENOSYS;
	return -1;
}

int pipc_unlink(const char *name) {
	errno = ENOSYS;
	return -1;
}

