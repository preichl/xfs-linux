// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#ifndef __XFS_SUPPORT_MRLOCK_H__
#define __XFS_SUPPORT_MRLOCK_H__

#include <linux/rwsem.h>

typedef struct {
	struct rw_semaphore	mr_lock;
} mrlock_t;

#if defined(DEBUG) || defined(XFS_WARN)
#define mrinit(smp, name)	init_rwsem(smp)
#else
#define mrinit(smp, name)	init_rwsem(smp)
#endif

#define mrlock_init(smp, t, n, s)	mrinit(smp, n)
#define mrfree(smp)		do { } while (0)

static inline void mraccess_nested(struct rw_semaphore *s, int subclass)
{
	down_read_nested(s, subclass);
}

static inline void mrupdate_nested(struct rw_semaphore *s, int subclass)
{
	down_write_nested(s, subclass);
}

static inline int mrtryaccess(struct rw_semaphore *s)
{
	return down_read_trylock(s);
}

static inline int mrtryupdate(struct rw_semaphore *s)
{
	if (!down_write_trylock(s))
		return 0;
	return 1;
}

static inline void mrunlock_excl(struct rw_semaphore *s)
{
	up_write(s);
}

static inline void mrunlock_shared(struct rw_semaphore *s)
{
	up_read(s);
}

static inline void mrdemote(struct rw_semaphore *s)
{
	downgrade_write(s);
}

#endif /* __XFS_SUPPORT_MRLOCK_H__ */
