#ifndef _SIGNAL_H
#if defined __need_sig_atomic_t || defined __need_sigset_t
# include <signal/signal.h>
#else
# include <signal/signal.h>

# ifndef _ISOMAC
libc_hidden_proto (sigemptyset)
libc_hidden_proto (sigfillset)
libc_hidden_proto (sigaddset)
libc_hidden_proto (sigdelset)
libc_hidden_proto (sigismember)
extern int __sigpause (int sig_or_mask, int is_sig);
libc_hidden_proto (__sigpause)
libc_hidden_proto (raise)
libc_hidden_proto (__libc_current_sigrtmin)
libc_hidden_proto (__libc_current_sigrtmax)
libc_hidden_proto (_sys_siglist)

/* Now define the internal interfaces.  */
extern __sighandler_t __bsd_signal (int __sig, __sighandler_t __handler);
extern int __kill (__pid_t __pid, int __sig);
extern int __sigaction (int __sig, const struct sigaction *__restrict __act,
			struct sigaction *__restrict __oact);
libc_hidden_proto (__sigaction)
extern int __sigblock (int __mask);
extern int __sigsetmask (int __mask);
extern int __sigprocmask (int __how,
			  const sigset_t *__set, sigset_t *__oset);
extern int __sigsuspend (const sigset_t *__set);
libc_hidden_proto (__sigsuspend)
#ifndef NO_CANCELLATION
extern int __sigsuspend_nocancel (const sigset_t *__set) attribute_hidden;
#endif
extern int __sigwait (const sigset_t *__set, int *__sig);
libc_hidden_proto (__sigwait)
extern int __sigwaitinfo (const sigset_t *__set, siginfo_t *__info);
libc_hidden_proto (__sigwaitinfo)
extern int __sigtimedwait (const sigset_t *__set, siginfo_t *__info,
			   const struct timespec *__timeout);
libc_hidden_proto (__sigtimedwait)
extern int __sigqueue (__pid_t __pid, int __sig,
		       const union sigval __val);
#ifdef __USE_MISC
extern int __sigreturn (struct sigcontext *__scp);
#endif
extern int __sigaltstack (const struct sigaltstack *__ss,
			  struct sigaltstack *__oss);
extern int __libc_sigaction (int sig, const struct sigaction *act,
			     struct sigaction *oact);
libc_hidden_proto (__libc_sigaction)

extern int __default_sigpause (int mask);
extern int __xpg_sigpause (int sig);

/* Simplified sigemptyset() implementation without the parameter checking.  */
#undef __sigemptyset
#define __sigemptyset(ss) \
  ({ __builtin_memset (ss, '\0', sizeof (sigset_t)); 0; })


/* Allocate real-time signal with highest/lowest available priority.  */
extern int __libc_allocate_rtsig (int __high);

#  if IS_IN (rtld)
extern __typeof (__sigaction) __sigaction attribute_hidden;
extern __typeof (__libc_sigaction) __libc_sigaction attribute_hidden;
#  endif
# endif
#endif
#endif
