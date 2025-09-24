// simwrap.c — Windows (MinGW) + SBCL linkable runtime named "libsbcl.so"
#ifdef _WIN32
  #define API __declspec(dllexport)
  #include <windows.h>
#else
  #define API __attribute__((visibility("default")))
  #include <dlfcn.h>
#endif

#include <stddef.h>

/* From SBCL's linkable runtime (provided by libsbcl.so) */
extern int initialize_lisp(int argc, char** argv);

/* Function pointer types */
typedef int  (*fn_sim_start_t)(void);
typedef void (*fn_sim_stop_t)(void);

/* Cached after init */
static fn_sim_start_t p_sim_start = NULL;
static fn_sim_stop_t  p_sim_stop  = NULL;

static int resolve_callables(void) {
#ifdef _WIN32
  /* Your runtime is libsbcl.so (a DLL with a .so name). */
  HMODULE h = GetModuleHandleA("libsbcl.so");
  if (!h) return -1;

  /* SBCL exports DATA symbols named "sim_start"/"sim_stop".
     GetProcAddress returns the ADDRESS OF THE VARIABLE,
     which itself holds the function pointer. Deref once. */
  void* a = (void*)GetProcAddress(h, "sim_start");
  void* b = (void*)GetProcAddress(h, "sim_stop");
  if (!a || !b) return -2;

  p_sim_start = *(fn_sim_start_t*)a;
  p_sim_stop  = *(fn_sim_stop_t*)b;
  return (p_sim_start && p_sim_stop) ? 0 : -3;
#else
  void *a = dlsym(RTLD_DEFAULT, "sim_start");
  void *b = dlsym(RTLD_DEFAULT, "sim_stop");
  if (!a || !b) return -1;
  p_sim_start = *(fn_sim_start_t*)a;
  p_sim_stop  = *(fn_sim_stop_t*)b;
  return 0;
#endif
}

/* Initialize SBCL with your core, then resolve callables */
API int sim_init(const char* core_path) {
  char* argv[] = {"", "--noinform", "--core", (char*)core_path};
  int rc = initialize_lisp(4, argv);
  if (rc != 0) return rc;
  return resolve_callables();
}

API int sim_start_now(void) { return p_sim_start ? p_sim_start() : -1; }
API void sim_stop_now(void) { if (p_sim_stop) p_sim_stop(); }
