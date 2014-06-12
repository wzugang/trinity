/*
 * SYSCALL_DEFINE3(write, unsigned int, fd, const char __user *, buf, size_t, count)
 */
#include <stdlib.h>
#include "arch.h"	// page_size
#include "maps.h"
#include "sanitise.h"
#include "shm.h"
#include "syscall.h"
#include "trinity.h"

static void sanitise_write(struct syscallrecord *rec)
{
	if ((rand() % 100) > 50)
		rec->a3 = 1;
	else
		rec->a3 = rand() % page_size;
}

struct syscallentry syscall_write = {
	.name = "write",
	.num_args = 3,
	.sanitise = sanitise_write,
	.arg1name = "fd",
	.arg1type = ARG_FD,
	.arg2name = "buf",
	.arg2type = ARG_NON_NULL_ADDRESS,
	.arg3name = "count",
	.arg3type = ARG_LEN,
	.flags = NEED_ALARM,
};
