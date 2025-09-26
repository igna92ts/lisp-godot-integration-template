#ifndef _sim_h
#define _sim_h

#if defined(API_BUILD)
#  if defined(_WIN64)
#    define LIB_API __declspec(dllexport)
#  elif defined(__ELF__)
#    define LIB_API __attribute__ ((visibility ("default")))
#  else
#    define LIB_API
#  endif
#else
#  if defined(_WIN64)
#    define LIB_API __declspec(dllimport)
#  else
#    define LIB_API
#  endif
#endif

extern LIB_API void (*lisp_release_handle)(void* handle);
extern LIB_API int  (*lisp_handle_eq)(void* a, void* b);
extern LIB_API void (*lisp_enable_debugger)();
extern LIB_API void (*lisp_disable_debugger)();
extern LIB_API void (*lisp_gc)();

extern LIB_API int init_sim(void);

// Value with names coming from lisp
extern int  (*simstart)(void);
extern void (*simstop)(void);
extern int (*start_repl)(int);

// This wrappers need to be here, its a pointer thing
// https://mstmetent.blogspot.com/2022/04/using-lisp-libraries-from-other.html
extern LIB_API int start_simulation(void);
extern LIB_API void stop_simulation(void);
extern LIB_API int start_simulation_repl(int);

#endif
