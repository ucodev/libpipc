#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <pipc/pipc.h>

#define PIPC_KEY	(pipck_t) 1234
#define MASTER_ID	0x0A0001
#define SLAVE_ID	0x0B0002

int main(void) {
	pipcd_t *pipcd = NULL;
	long src_id = 0, dst_id = MASTER_ID;
	char msg[64];
	ssize_t ret = 0;

	if (!(pipcd = pipc_master_register(PIPC_KEY, MASTER_ID, 512, 16, 0600))) {
		fprintf(stderr, "pipc_slave_register(): %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if ((ret = pipc_recv(pipcd, &src_id, &dst_id, msg, sizeof(msg))) < 0) {
		fprintf(stderr, "pipc_send(): %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	printf("RECEIVED[ret: %zd, src: 0x%lX, dst: 0x%lX]: %s\n", ret, src_id, dst_id, msg);

	if (pipc_master_unregister(pipcd) < 0) {
		fprintf(stderr, "pipc_slave_unregister(): %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	return 0;
}

