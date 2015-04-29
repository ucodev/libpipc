#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <pipc/pipc.h>

#define PIPC_KEY	(pipck_t) 1234
#define MASTER_ID	0x0A0001
#define SLAVE_ID	0x0B0002
#define IPC_MSG		"Hello master!"

int main(void) {
	pipcd_t *pipcd = NULL;

	puts("Start the 'master' then press a key to continue...");

	getchar();

	if (!(pipcd = pipc_slave_register(PIPC_KEY, SLAVE_ID, 512, 16, 0600))) {
		fprintf(stderr, "pipc_slave_register(): %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if (pipc_send(pipcd, SLAVE_ID, MASTER_ID, IPC_MSG, sizeof(IPC_MSG)) < 0) {
		fprintf(stderr, "pipc_send(): %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if (pipc_slave_unregister(pipcd) < 0) {
		fprintf(stderr, "pipc_slave_unregister(): %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	return 0;
}

