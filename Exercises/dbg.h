/**
CPP replaces macros with the expanded version of their definition, and it will do this recursively, expanding all of the macros in macros.CPP is just a recursively templating system.
*/
#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", \
						__FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

/**
Replaces itself with a call to fprintf to stderr. The only tricky part of this macro is the use of ... in the definition log_err(M, ...). What this does is let you pass variable arguments to the macro, so you can pass in the arguments that should go to fprintf. How do the get injected into the fprintf call? using ##__VA_ARGS__, which is telling the CPP to take the args entered where the ... is, and inject them at that part of the fprintf call.
*/
#define log_err(M, ...) fprintf(stderr, \
		"[ERROR] (%s:%d errno: %s) " M "\n", __FILE__, __LINE__,\
		clean_errno(), ##__VA_ARGS__)
		
		
#define log_warn(M, ...) fprintf(stderr, \
		"[WARN] (%s:%d errno: %s) " M "\n", __FILE__, __LINE__,\
		clean_errno(), ##__VA_ARGS__)
		
#define log_info(M, ...) fprintf(stderr, \
		"[INFO] (%s:%d errno: %s) " M "\n", __FILE__, __LINE__,\
		clean_errno(), ##__VA_ARGS__)
/**
If A is false, then clear errno and goto the error label. The check macro is being replaced with the if-statement.
*/
#define check(A, M, ...) if(!(A)) {\
	log_err(M, ##__VA_ARGS__); errno=0; goto error;}
	
#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__);\
	errno=0; goto error;}
	
#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
	errno=0; goto error; }

#endif
