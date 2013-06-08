#ifndef __SPINLOCK_H
#define __SPINLOCK_H

/* Code to manage spinlocks for SMP access to the shared memory logging */
/* buffer used by the fig wrapper program (logging daemon).             */
/* Lifted wholesale from the Linux 2.4 kernel sources                   */

/*
 * Your basic SMP spinlocks, allowing only a single CPU anywhere
 */

typedef struct {
	volatile unsigned int lock;
} spinlock_t;

#define SPIN_LOCK_UNLOCKED (spinlock_t) { 1 }

#define spin_lock_init(x)	do { *(x) = SPIN_LOCK_UNLOCKED; } while(0)

/*
 * Simple spin lock operations.  There are two variants, one clears IRQ's
 * on the local processor, one does not.
 *
 * We make no fairness assumptions. They have a cost.
 */

#define spin_is_locked(x)	(*(volatile char *)(&(x)->lock) <= 0)

// #define spin_unlock_wait(x)	do { barrier(); } while(spin_is_locked(x))

#define spin_lock_string \
	"\n1:\t" \
	"lock ; decb %0\n\t" \
	"js 2f\n" \
	".section .text.lock,\"ax\"\n" \
	"2:\t" \
	"cmpb $0,%0\n\t" \
	"rep;nop\n\t" \
	"jle 2b\n\t" \
	"jmp 1b\n" \
	".previous"

/*
 * This works. Despite all the confusion.
 */
#define spin_unlock_string \
	"movb $1,%0"

static inline int spin_trylock(spinlock_t *lock)
{
	char oldval;
	__asm__ __volatile__(
		"xchgb %b0,%1"
		:"=q" (oldval), "=m" (lock->lock)
		:"0" (0) : "memory");
	return oldval > 0;
}

static inline void spin_lock(spinlock_t *lock)
{
	__asm__ __volatile__(
		spin_lock_string
		:"=m" (lock->lock) : : "memory");
}

static inline void spin_unlock(spinlock_t *lock)
{
	__asm__ __volatile__(
		spin_unlock_string
		:"=m" (lock->lock) : : "memory");
}

#endif /* __SPINLOCK_H */
