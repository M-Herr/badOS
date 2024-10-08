#ifndef _ICXXABI_H
	#define _ICXXABI_H

	#define ATEXIT_MAX_FUNCS	128
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
typedef unsigned uarch_t;


struct atexit_func_entry_t
{
	/*
	* Each member is at least 4 bytes large. Such that each entry is 12bytes.
	* 128 * 12 = 1.5KB exact.
	**/
	void (*destructor_func)(void *);
	void *obj_ptr;
	void *dso_handle;
};

extern "C" void _Unwind_Resume();
extern "C" void __gxx_personality_v0();
extern "C" void __cxa_pure_virtual();

int __cxa_atexit(void (*f)(void *), void *objptr, void *dso);
void __cxa_finalize(void *f);

	#ifdef __cplusplus
	};
	#endif

#endif